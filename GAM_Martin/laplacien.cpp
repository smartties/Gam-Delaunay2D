#include "laplacien.h"
#include "circulateur.h"

#include <QDebug>
#include <iostream>


namespace Laplacien
{
    Vec3 courburetoHSVtoRGB(float courb)
    {
        float div = courb / 60.f;
        float X = fmod(div, 2);

        if(div < 1) return {0, X,1};
        if(div < 2) return {0, 1,X};
        if(div < 3) return {X, 1,0};
        if(div < 4) return {1, X,0};
        if(div < 5) return {1, 0,X};
        if(div < 6) return {X, 0,1};

        return Vec3(0, 0, 0);
    }


    float aireAutourDe(Mesh &mesh, int ind)
    {
            Vertex &vertex = mesh.mVerticles[ind];
            Circulator_on_faces vertexIncident = mesh.incident_faces(vertex);

            Circulator_on_faces cvBegin = vertexIncident;
            float aire = 0;

            do
            {
                Vertex centreGravite = mesh.getBarycentre(vertexIncident.getCurrentIndex());
                int localId = vertexIncident->findLocalId(ind);

                Vertex vectA = (vertex + mesh.mVerticles[vertexIncident->vertexIndex[ (localId == 1)? 0 : 1 ]]) / 2.f;
                Vertex vectB = (vertex + mesh.mVerticles[vertexIncident->vertexIndex[ (localId == 2)? 0 : 2 ]]) / 2.f;

                float aireABC = (vectA - vertex).cross(vectB - vertex).length() / 2.f;
                float aireDBC = (centreGravite - vectA).cross(vectB - vectA).length() / 2.f;
                aire+= aireABC + aireDBC;
            }while(++vertexIncident != cvBegin);

            return aire;
    }

    void computeLaplacienMesh(Mesh &mesh, int flag)
    {
        for(Iterator_on_vertices iov = mesh.vertices_begin(); iov.hasNext(); ++iov)
        {
            int ind = iov.getCurrentIndex();

            Vertex &mVertex = mesh.mVerticles[ind];
            Vertex laplacien;

            float AireAutourdeI = aireAutourDe(mesh, ind);

            Circulator_on_vertices cov = mesh.adjacent_vertices(mVertex);
            Vertex vtxPrecedent = *cov;
            Circulator_on_vertices start = ++cov;

            do{
                Vertex prej = *cov;
                Vertex ai = mVertex - vtxPrecedent;
                Vertex aj = prej - vtxPrecedent;
                ++cov;
                Vertex vtxSuivant = *cov;
                Vertex bi = mVertex - vtxSuivant;
                Vertex bj = prej - vtxSuivant;

                //dot=...cos()
                //cross= ...sin()
                //cot = dot/||cross||
                float cotAlpha = ai.dot(aj) / ai.cross(aj).length();
                float cotBeta  = bi.dot(bj) / bi.cross(bj).length();
                float sommeCot = cotAlpha + cotBeta;

                laplacien.x += sommeCot * ( prej.x - mVertex.x);
                laplacien.y += sommeCot * ( prej.y - mVertex.y);
                laplacien.z += sommeCot * ( prej.z - mVertex.z);

                vtxPrecedent = prej;

            }while(cov != start);

            laplacien = laplacien / ( 2.f * AireAutourdeI);

            float K = std::sqrt(laplacien.dot(laplacien)); // équivalent à laplacien.length();

            //printf("flag %d\n", flag);
            if(flag == COMPUTE_COURBURE )
            {
                Vec3 clr = courburetoHSVtoRGB(K/2.f);
                mesh.mVerticles[ind].setRGB(clr.x, clr.y, clr.z);

                //mesh.mVerticles[ind].setRGB(K/100.f, K/100.f, K/100.f);
            }
            else
            {
                //K = K / (180.f); //M_PI
                //K = std::clamp(K, 0.f, 1.f);

                if(flag == COMPUTE_LAPLACIEN_X) K = laplacien.x;
                else if(flag == COMPUTE_LAPLACIEN_Y) K = laplacien.y;
                else if(flag == COMPUTE_LAPLACIEN_Z) K = laplacien.z;
                else Q_ASSERT("pas de flag correspondant pour le laplacien" && 0);

                /*static float mmin = K, mmax = K;
                mmin = std::min(mmin, K);
                mmax = std::max(mmax, K);
                printf("%f > %f %f\n", K, mmin, mmax);*/


                if(0)
                {
                    K =  std::clamp<float>( 0.5*(K/360.f), 0.f, 1.f);
                    Vec3 clr = courburetoHSVtoRGB(K*360);
                    mesh.mVerticles[ind].setRGB(clr.x, clr.y, clr.z);
                }
                else if(1)
                {
                    K =  std::clamp<float>( (K/240.f), 0.f, 1.f);
                    mesh.mVerticles[ind].setRGB(K, K, K);
                }



            }

        }
    }

}
