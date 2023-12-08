#include "mesh.h"
#include "circulateur.h"
#include "laplacien.h""

#include <algorithm>
#include <iostream>
#include <fstream>
#include <QDebug>
#include <queue>





void Mesh::makeTetraedre(float w)
{
    mVerticles.emplace_back(0, 0, 1);
    mVerticles.emplace_back(-w, -w, 0);
    mVerticles.emplace_back(0, w, 0);
    mVerticles.emplace_back(w, -w, 0);

    mFaces.emplace_back(0, 1, 2);
    mFaces.emplace_back(2, 3, 0);
    mFaces.emplace_back(0, 3, 1);
    mFaces.emplace_back(1, 3, 2);

    generateTopology();
}

Mesh::Mesh()
{
    hasPointinfini = false;
}

void Mesh::reset()
{
    mVerticles.clear();
    mFaces.clear();

}

void Mesh::setPointInfini(bool v)
{
    printf("set point infini %d\n", v);
    //le point infini est toujours le premier vertex
    if(v == true)
    {
        hasPointinfini = true;

        mVerticles[0].x = 0;
        mVerticles[0].y = 0;
        mVerticles[0].z = -100;//on créer le point infini
    }
    else
    {
        hasPointinfini = false;

        mVerticles[0].x = 0;
        mVerticles[0].y = 0;
        mVerticles[0].z = 0;
    }
};


void Mesh::reajustePremiertetra(Vertex a, Vertex b, Vertex c)
{
    mVerticles[1] = a;
    mVerticles[2] = b;
    mVerticles[3] = c;
}

//

Iterator_on_faces Mesh::faces_begin()
{
    return Iterator_on_faces(*this, 0);// le premier elem
}
Iterator_on_faces Mesh::faces_past_the_end()
{
    return Iterator_on_faces(*this, mFaces.size());// le dernier elem
}

Iterator_on_vertices Mesh::vertices_begin()
{
    return Iterator_on_vertices(*this, 0);// le premier elem
}
Iterator_on_vertices Mesh::vertices_past_the_end()
{
    return Iterator_on_vertices(*this, mFaces.size());// le dernier elem
}


Circulator_on_faces Mesh::incident_faces(Vertex &v)
{
    return Circulator_on_faces(*this, v);
}
Circulator_on_vertices Mesh::adjacent_vertices(Vertex &v)
{
    return Circulator_on_vertices(*this, v);
}


void Mesh::generateTopology()
{
    std::unordered_map<Mpair, Mpair, pair_hash> historiqueEdge;

    for(Iterator_on_faces it = faces_begin(); it.hasNext(); ++it)
    {
        Face &f = *it;

        Vertex &v0 = mVerticles[f.vertexIndex[0]];
        Vertex &v1 = mVerticles[f.vertexIndex[1]];
        Vertex &v2 = mVerticles[f.vertexIndex[2]];

        v0.indexFaceIncident = it.getCurrentIndex();
        v1.indexFaceIncident = it.getCurrentIndex();
        v2.indexFaceIncident = it.getCurrentIndex();

        for(int j = 0; j < 3; ++j)
        {
            int scd = (j +1) % 3;
            int thrd = (j +2) % 3;

            int minInd, maxInd;
            //on défini les edges (conseillé en CM, pour éviter de devoir faire 2 recherches)
            minInd = std::min(f.vertexIndex[j], f.vertexIndex[scd]);
            maxInd = std::max(f.vertexIndex[j], f.vertexIndex[scd]);
            Mpair edge = {minInd, maxInd};

            auto location_it = historiqueEdge.find(edge);
            if( location_it == historiqueEdge.end())
            {
                Mpair pairFaceGlobalFaceLocal = {it.getCurrentIndex(), thrd};

                historiqueEdge.insert({edge, pairFaceGlobalFaceLocal });

                //Si l'edge n'est pas dans l'historique
                mVerticles[f.vertexIndex[j]].indexFaceIncident = it.getCurrentIndex();
            }
            else
            {
                //Si l'edge est dans l'historique on ajoute la face adjacente à la face à l'indice du sommet opposée à l'edge
                Mpair pairFaceGlobalFaceLocal = location_it->second;

                //
                f.adjFaceIndex[thrd] = pairFaceGlobalFaceLocal.first;
                //
                mFaces[pairFaceGlobalFaceLocal.first].adjFaceIndex[pairFaceGlobalFaceLocal.second] = it.getCurrentIndex();

                //qInfo() << "CAS B----------- set adjacent globalFaceIndex" << pairFaceGlobalFaceLocal.first << " localFAceindex" << pairFaceGlobalFaceLocal.second;
            }
        }
    }

    computeLaplacien();
}


void Mesh::computeLaplacien()
{
    Laplacien::computeLaplacienMesh(*this, flagLaplacien);
}


bool Mesh::loadPointsTxt(std::string name)
{
    if(name.empty())
        return false;

    lastNameLoad2D = name;
    std::ifstream ifs;
    ifs.open(name);
    if(ifs.bad())
    {
        std::cout<<"Impossible d'ouvrir le fichier "<< name <<" en lecture \n";
        return false;
    }

    size_t nbPoints = 0;
    std::string unusedString;

    bool success = true;

    success = success && ifs >> nbPoints;

    qInfo() << "success load " << success << "nbPoints " << nbPoints;
    std::vector<Vertex> points;

    for(int i = 0; i < nbPoints; i++)
    {
        double x, y, z;

        success = success && ifs >> x;
        success = success && ifs >> y;
        success = success && ifs >> z;

        points.push_back( Vertex(x, y, z) );

        //printf("%f %f %f\n", x, y, z);
    }

    ifs.close();

    //return points;

    Vertex pmin = points[0], pmax = points[1];
    for(int i = 0; i < points.size(); i++)
    {
        //points[i].z = 0;

        if(pmin.x > points[i].x) pmin.x = points[i].x;
        if(pmin.y > points[i].y) pmin.y = points[i].y;
        if(pmin.z > points[i].z) pmin.z = points[i].z;

        if(pmax.x < points[i].x) pmax.x = points[i].x;
        if(pmax.y < points[i].y) pmax.y = points[i].y;
        if(pmax.z < points[i].z) pmax.z = points[i].z;
    }

    float ratio = std::max(pmin.length(), pmax.length());

    assert("ratio doit etre strict positif" && ratio > 0);

    pmin = pmin / (ratio * 0.95);
    pmax = pmax / (ratio * 0.95);


    pmin.log("pmin");
    pmax.log("pmax");

    for(int i = 0; i < points.size(); i++)
    {
        points[i] = points[i] / ratio;
    }

    if(points.size() > 3)
    {
        if( Face::orientation( points[0], points[1], points[2]) < 0 )
            reajustePremiertetra(points[0],points[1],points[2]);
        else
            reajustePremiertetra(points[0],points[2],points[1]);

        generateTopology();
    }

    setPointInfini(true);

    for(int i = 3; i < points.size(); i++)
        insertionDePoint(points[i]);

    processDelaunay();
    generateTopology();

    return true;
}

bool Mesh::loadMeshOff(std::string name)
{
    if(name.empty())
        return false;

    lastNameLoad3D = name;
    std::ifstream ifs;
    ifs.open(name);
    if(ifs.bad())
    {
        std::cout<<"Impossible d'ouvrir le fichier "<< name <<" en lecture \n";
        return false;
    }


    size_t nbVertices = 0, nbFaces = 0, unusedValue = 0;
    std::string unusedString;

    bool success = true;

    success = success && ifs >> unusedString;//OFF

    if(unusedString != "OFF" && unusedString != "Off" && unusedString != "off")
        ifs.seekg(0, std::ios::beg);

    success = success && ifs >> nbVertices;//nbVertices
    success = success && ifs >> nbFaces;//face
    success = success && ifs >> unusedValue;//0

    qInfo() << "success load " << success << "nbVertices " << nbVertices << " nbFaces " << nbFaces << " unusedValue " << unusedValue;

    for(int i = 0; i < nbVertices; i++)
    {
        double x, y, z;

        success = success && ifs >> x;
        success = success && ifs >> y;
        success = success && ifs >> z;

        mVerticles.push_back( Vertex(x, y, z) );
    }

    for(int i = 0; i < nbFaces; i++)
    {
        int i0, i1, i2, nbVertexParFace = 0;

        success = success && ifs >> nbVertexParFace;

        success = success && ifs >> i0;
        success = success && ifs >> i1;
        success = success && ifs >> i2;

        mFaces.push_back( Face(i0, i1, i2));
    }

    qInfo() << "success load " << success << "nbVertices " << nbVertices << " nbFaces " << nbFaces << " unusedValue " << unusedValue;

    ifs.close();

    return success && nbVertices > 0;
}

bool Mesh::writeMeshOff(std::string name)
{
    std::ofstream ofs;

    // Open a file for writing (create it if it doesn't exist)
    ofs.open(name);

    // Check if the file is opened successfully
    if (!ofs.is_open()) {
        // Handle error
        printf("couldn't wirte\n");
        return 1;
    }

    // Write data to the file
    ofs << "OFF" << std::endl;

    ofs << mVerticles.size() << " " << mFaces.size() << " 0" << std::endl;

    for(int i = 0; i < mVerticles.size(); i++)
    {
        ofs << mVerticles[i].x << " " << mVerticles[i].y << " " << mVerticles[i].z << std::endl;
    }

    for(int i = 0; i < mFaces.size(); i++)
    {
        ofs << mFaces[i].vertexIndex[0] << " " << mFaces[i].vertexIndex[1] << " " << mFaces[i].vertexIndex[2] << std::endl;
    }

    printf("tERZTRET\n");

    // Close the file
    ofs.close();
}

void Mesh::triangleSplit(int faceId, int vtxId)
{
    TrioId faceTrio = mFaces[faceId].adjFaceIndex;

    Face trioFace[3] =
    {
        Face(mFaces[faceId].vertexIndex[0], mFaces[faceId].vertexIndex[1], vtxId),
        Face(mFaces[faceId].vertexIndex[1], mFaces[faceId].vertexIndex[2], vtxId),
        Face(mFaces[faceId].vertexIndex[2], mFaces[faceId].vertexIndex[0], vtxId)
    };

    mFaces[faceId] = trioFace[0];

    int nwFc[] = {faceId, addFace(trioFace[1]), addFace(trioFace[2])};
    mVerticles[vtxId].indexFaceIncident = nwFc[0];

    for(int i = 0; i < 3; i++)//pour les 3 nouveaux triangles, on met à jours les voisins et les infos locales sur les voisins
    {
        mFaces[nwFc[i]].adjFaceIndex[0] = nwFc[(i+1) % 3];
        mFaces[nwFc[i]].adjFaceIndex[1] = nwFc[(i+2) % 3];
        mFaces[nwFc[i]].adjFaceIndex[2] = faceTrio[(i + 2) % 3];

        mVerticles[mFaces[nwFc[i]].vertexIndex[0]].indexFaceIncident = nwFc[i];

        if(mFaces[mFaces[nwFc[i]].adjFaceIndex[2]].adjFaceIndex[0] == faceId) mFaces[mFaces[nwFc[i]].adjFaceIndex[2]].adjFaceIndex[0] = nwFc[i];
        else if(mFaces[mFaces[nwFc[i]].adjFaceIndex[2]].adjFaceIndex[1] == faceId) mFaces[mFaces[nwFc[i]].adjFaceIndex[2]].adjFaceIndex[1] = nwFc[i];
        else mFaces[mFaces[nwFc[i]].adjFaceIndex[2]].adjFaceIndex[2] = nwFc[i];
    }
}

void Mesh::edgeFlip(int faceA, int faceB)
{
    Face &rfA = mFaces[faceA];
    Face &rfB = mFaces[faceB];
    int indLocalOppB = rfA.findLocalOpposeeId(faceB);
    int indLocalOppA = rfB.findLocalOpposeeId(faceA);

    if(indLocalOppB != -1 && indLocalOppA != -1)
    {
        int newA = (indLocalOppB + 1) % 3, s1nn = (indLocalOppB + 2) % 3;
        int newB = (indLocalOppA + 1) % 3, s2nn = (indLocalOppA + 2) % 3;

        rfA.adjFaceIndex[indLocalOppB] = rfB.adjFaceIndex[s2nn];
        rfB.adjFaceIndex[indLocalOppA] = rfA.adjFaceIndex[s1nn];
        rfA.adjFaceIndex[s1nn] = faceB;
        rfB.adjFaceIndex[s2nn] = faceA;

        mVerticles[rfA.vertexIndex[newA]].indexFaceIncident = faceB;
        mVerticles[rfB.vertexIndex[newB]].indexFaceIncident = faceA;

        //on flip les vertex
        rfA.vertexIndex[newA] = rfB.vertexIndex[indLocalOppA];
        rfB.vertexIndex[newB] = rfA.vertexIndex[indLocalOppB];
        //

        int b = mFaces[rfA.adjFaceIndex[indLocalOppB]].findLocalOpposeeId(faceB);
        int c = mFaces[rfB.adjFaceIndex[indLocalOppA]].findLocalOpposeeId(faceA);
        mFaces[rfA.adjFaceIndex[indLocalOppB]].adjFaceIndex[b] = faceA;
        mFaces[rfB.adjFaceIndex[indLocalOppA]].adjFaceIndex[c] = faceB;
    }
}


int Mesh::locatingFace(const Vertex &vtx)
{
    int faceId = 1;
    while(mFaces[faceId].infini())
    {
        int localId = mFaces[faceId].findLocalId(0);

        Q_ASSERT("face infinie n'a pas de point infini (pas possible)" && localId != -1);
        faceId = mFaces[faceId].adjFaceIndex[localId];
    }

    int newFaceId = -1;

    while(true)
    {
        Vertex ps[] = {mVerticles[mFaces[faceId].vertexIndex[0]],
                       mVerticles[mFaces[faceId].vertexIndex[1]],
                       mVerticles[mFaces[faceId].vertexIndex[2]] };

        int orient = -2;
        if(newFaceId < 0)
        {
            newFaceId = 2;
            orient = Face::orientation(ps[0], ps[1], vtx);
        }

        int end = newFaceId;
        if(orient != -1)
        for(newFaceId = (newFaceId + 1) % 3; newFaceId != end; newFaceId = (newFaceId + 1) % 3)
        {
            orient = Face::orientation(ps[(newFaceId + 1) % 3], ps[(newFaceId + 2) % 3], vtx);

            if(orient < 0)
                break;
        }

        if(orient >= 0)
            break;

        int swapId = faceId;
        faceId = mFaces[faceId].adjFaceIndex[newFaceId];
        newFaceId = mFaces[faceId].findLocalOpposeeId(swapId);

        if(mFaces[faceId].infini())//si on rencontre une face infini dans notre forme convexe, on arrete la recherche
            break;
    }

    return faceId;
}

int Mesh::insertionDePoint(const Vertex &vtx)
{
    int faceId = locatingFace(vtx);

    Q_ASSERT(faceId != -1 && "Pas de face trouvé, impossible");

    int insertedId = addVertex(vtx, faceId);

    bool faceFoundInfini = mFaces[faceId].infini();
    triangleSplit(faceId, insertedId);

    if(faceFoundInfini == false)
        return insertedId;

    if(!mFaces[faceId].infini())// on vérifie que la nouvelle face
    {
        //si c'est le cas, on prend un des faces adjacente qui partage un sommet (hors point inséré)
        int oldFaceId = faceId;
        faceId = mFaces[faceId].adjFaceIndex[(mFaces[faceId].findLocalId(insertedId) + 2) %3];

        if(mFaces[faceId].infini() == false)
        {
            faceId = oldFaceId;
            faceId = mFaces[faceId].adjFaceIndex[(mFaces[faceId].findLocalId(insertedId) + 1) %3];// on essaie avec l'autre
        }

        Q_ASSERT( mFaces[faceId].infini() && "On n'a pas de face infini sur lequel inséré notre point hors shape convexe");
    }


    Face &constantFaceNonFlippable = mFaces[mFaces[faceId].adjFaceIndex[mFaces[faceId].findLocalId(0)]];
    int localIdOfInsertedPointInFace = constantFaceNonFlippable.findLocalId(insertedId);

    int secondSensStartFaceID = (localIdOfInsertedPointInFace + 1 ) % 3;
    int premierSensStartFaceID = (localIdOfInsertedPointInFace + 2 ) % 3;

    for(int sens = 0; sens < 2; sens++)
    {
        bool keepCirculatingOnInfiniteFace = true;
        int faceCirc = sens == 0 ? constantFaceNonFlippable.adjFaceIndex[premierSensStartFaceID] : constantFaceNonFlippable.adjFaceIndex[secondSensStartFaceID];

        while(keepCirculatingOnInfiniteFace)
        {
            keepCirculatingOnInfiniteFace = false;
            Face face = mFaces[faceCirc];

            if(!face.infini())//si la face n'est pas infini, ont en choisi qui l'est
            {
                int newFaceId = (face.findLocalId(insertedId) + 2 - sens) % 3;
                faceCirc = face.adjFaceIndex[newFaceId];
                face = mFaces[faceCirc];

                Q_ASSERT(face.infini() && "La nouvelle face n'est tjrs pas infinie");
            }

            int localInsertId = face.findLocalId(insertedId);
            Q_ASSERT(localInsertId != -1);
            int faceOppo = face.adjFaceIndex[localInsertId];
            Face &refFaceOpp = mFaces[faceOppo];
            int fVertexnext = refFaceOpp.vertexIndex[refFaceOpp.findLocalOpposeeId(faceCirc)];
            //printf("f %d %d\n", f.infini(), mFaces[fOpposite].infini());

            int signOrientation = Face::orientation(mVerticles[insertedId], mVerticles[face.vertexIndex[(localInsertId + 2 - sens) % 3]], mVerticles[fVertexnext]);
            if(  sens == 0 ? signOrientation < 0 : signOrientation > 0 )
            {
                edgeFlip(faceCirc, faceOppo);
                keepCirculatingOnInfiniteFace = true;//on a fait un flip, donc on refait un tours de boucle pour voir le voisin dans le sens attribué
            }
        }
    }

    return insertedId;
}

void Mesh::insertionDePointDelaunay(const Vertex &vtx)
{
    int newPointId = insertionDePoint(vtx);
    Q_ASSERT(newPointId != -1 && "insertionDePointDelaunay failled");

    Circulator_on_faces circFace = incident_faces(mVerticles[newPointId]);
    Circulator_on_faces end = circFace;
    std::vector<Mpair> queue;

    int compt = 0;
    for(; compt == 0 || circFace != end; compt++)
    {
        Face &face = mFaces[circFace.getCurrentIndex()];
        if(face.infini() == false)
        for(int i = 0; i < 3; ++i)
        {
            if(mFaces[face.adjFaceIndex[i]].infini() == false)
                if(!isEdgeDelaunay(circFace.getCurrentIndex(), face.adjFaceIndex[i]))
                    queue.emplace_back(circFace.getCurrentIndex(), face.adjFaceIndex[i]);
        }
        ++circFace;
    }

    flipEdges(queue);
}


Vertex liftOperator(Vertex &vert)
{
    return Vertex(vert.x, vert.y, pow(vert.x, 2) + pow(vert.y, 2));
}

int Mesh::in_cercle(Face &face, Vertex &vert)
{
    Vertex A = liftOperator(mVerticles[face.vertexIndex[0]]);
    Vertex B = liftOperator(mVerticles[face.vertexIndex[1]]);
    Vertex C = liftOperator(mVerticles[face.vertexIndex[2]]);

    Vertex S = liftOperator(vert);

    Vertex BA = B - A, CA = C - A, SA = S - A;

    float signe = -BA.cross(CA).dot(SA);

    //CM 4, page 134

    if(signe > 0)
        return 1;
    if(signe < 0)
        return -1;
    return 0;
}


bool Mesh::isEdgeDelaunay(int f1, int f2)
{
    Face &face = mFaces[f1];
    Face &faceOpposee = mFaces[f2];

    int id = faceOpposee.findLocalOpposeeId(f1);

    Q_ASSERT(id != -1 && faceOpposee.vertexIndex[id] != -1 && "edgDelaunay id -1");

    Vertex &s = mVerticles[ faceOpposee.vertexIndex[id] ];
    return in_cercle(face, s) <= 0;
}

void Mesh::flipEdges(std::vector<Mpair> &nodeQ)
{
    while(!nodeQ.empty())
    {
        Mpair node = nodeQ[0]; // ont prend le plus ancien
        nodeQ.erase(nodeQ.begin());

        if(mFaces[node.first].findLocalOpposeeId(node.second) < 0 || mFaces[node.second].findLocalOpposeeId(node.first) < 0 || mFaces[node.first].infini() || mFaces[node.second].infini() )
        {
            //printf("skip\n");
        }
        else if(!isEdgeDelaunay(node.first, node.second))
        {
            Face &face = mFaces[node.first];
            Face &faceOpp = mFaces[node.second];

            edgeFlip(node.first, node.second);

            int idFaceOppinFace = face.findLocalOpposeeId(node.second);
            int idFaceinFaceOpp = faceOpp.findLocalOpposeeId(node.first);
            for(int i = 1; i < 3; ++i)
            {
                int idItFace = (idFaceOppinFace + i) % 3;
                int idItFaceOpp = (idFaceinFaceOpp + i) % 3;

                if(!mFaces[face.adjFaceIndex[idItFace]].infini())
                    if(!isEdgeDelaunay(node.first, face.adjFaceIndex[idItFace]))
                        nodeQ.emplace_back(node.first, face.adjFaceIndex[idItFace]);

                if(!mFaces[faceOpp.adjFaceIndex[idItFaceOpp]].infini())
                    if(!isEdgeDelaunay(node.second, faceOpp.adjFaceIndex[idItFaceOpp]))
                        nodeQ.emplace_back(node.second, faceOpp.adjFaceIndex[idItFaceOpp]);
            }
        }
    }
}

void Mesh::processDelaunay()
{
    std::vector<Mpair> queue;

    for(Iterator_on_faces it = faces_begin(); it.hasNext(); ++it)
    {
        if(it->infini() == false)
        for(int i = 0; i < 3; ++i)
        {
            if(it->adjFaceIndex[i] >= it.getCurrentIndex() && mFaces[it->adjFaceIndex[i]].infini() == false )
            {
                if(in_cercle(mFaces[it->adjFaceIndex[i]], mVerticles[it->vertexIndex[i]]) >= 0)
                    queue.emplace_back(it.getCurrentIndex(), it->adjFaceIndex[i]);
            }
        }
    }

    flipEdges(queue);
}
