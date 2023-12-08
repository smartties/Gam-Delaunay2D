#ifndef MESH_H
#define MESH_H

#include <set>
#include <vector>
#include <array>

#include "mathtoolbox.h"

typedef std::pair<int32_t, int32_t> Mpair;

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

class Iterator_on_faces;
class Iterator_on_vertices;

class Circulator_on_faces;
class Circulator_on_vertices;



class Mesh
{
public:
    Mesh();

    void makeTetraedre(float w);

    void reset();

    bool loadPointsTxt(std::string name);
    bool loadMeshOff(std::string name);
    bool writeMeshOff(std::string name);


    void setPointInfini(bool v);
    void reajustePremiertetra(Vertex a, Vertex b, Vertex c);



    Iterator_on_faces faces_begin();
    Iterator_on_faces faces_past_the_end();

    Iterator_on_vertices vertices_begin();
    Iterator_on_vertices vertices_past_the_end();

    Circulator_on_faces incident_faces(Vertex &v);
    Circulator_on_vertices adjacent_vertices(Vertex &v);



    void triangleSplit(int fId, int pId);
    void edgeFlip(int fId1, int fId2);
    int locatingFace(const Vertex &p);
    int insertionDePoint(const Vertex &p);
    void insertionDePointDelaunay(const Vertex &p);


    int in_cercle(Face &face, Vertex &p);

    bool isEdgeDelaunay(int f1, int f2);

    void flipEdges(std::vector<Mpair> &nodeQ);
    void processDelaunay();

    void generateTopology();
    void computeLaplacien();


    int addVertex(const Vertex &p, int fId = -1)
    {
        mVerticles.emplace_back(p, fId);
        return mVerticles.size() - 1;
    }

    int addFace(const TrioId &sIds, const TrioId &fIds = TrioId())
    {
        mFaces.emplace_back(sIds, fIds);
        return mFaces.size() - 1;
    }

    int addFace(const Face &face)
    {
        return addFace(face.vertexIndex, face.adjFaceIndex);
    }

    Vertex getBarycentre(int ind)
    {
        return (mVerticles[mFaces[ind].vertexIndex[0]] + mVerticles[mFaces[ind].vertexIndex[1]]
               + mVerticles[mFaces[ind].vertexIndex[2]]) / 3.f;
    }

    Vertex getBarycoord(int ind, float i0, float i1, float i2)
    {
        return mVerticles[mFaces[ind].vertexIndex[0]] * i0 + mVerticles[mFaces[ind].vertexIndex[1]] * i1
                + mVerticles[mFaces[ind].vertexIndex[2]] * i2;
    }


    Vertex getNormal(int fId) const{
        const Face &tri = mFaces[fId];

        Vertex diffA = mVerticles[tri.vertexIndex[1]] - mVerticles[tri.vertexIndex[0]];
        Vertex diffB = mVerticles[tri.vertexIndex[2]] - mVerticles[tri.vertexIndex[0]];

        return diffA.cross(diffB).normalize();
    }


    std::vector<Vertex> mVerticles;
    std::vector<Face> mFaces;
    bool hasPointinfini;
    int flagLaplacien = 0x8;

    std::string lastNameLoad2D;
    std::string lastNameLoad3D;
};



#endif // MESH_H
