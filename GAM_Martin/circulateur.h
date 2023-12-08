#ifndef CIRCULATEUR_H
#define CIRCULATEUR_H

#include "mathtoolbox.h"
#include "mesh.h"

#include <iostream>






class Iterator_on_faces
{
public:
    int getCurrentIndex()
    {
        return index;
    }

    Face& operator*()
    {
        return meshRef.mFaces[index];
    }

    Iterator_on_faces& operator++()
    {
        index++;

        return *this;
    }

    Face* operator->()
    {
        return & meshRef.mFaces[index];
    }


    bool hasNext()
    {
        return index < meshRef.mFaces.size();
    }

    bool operator!=(const Iterator_on_faces& it)
    {
        return index != it.index;
    }


    Mesh &meshRef;
    int index;
    Iterator_on_faces(Mesh  &mesh, int index): meshRef(mesh)
    {
        this->index = index;
    }
};





class Iterator_on_vertices {
public:
    int getCurrentIndex()
    {
        return index;
    }

    Vertex& operator*()
    {
        return meshRef.mVerticles[index];
    }

    Iterator_on_vertices& operator++()
    {
        index++;
        return *this;
    }

    Vertex* operator->()
    {
        return &meshRef.mVerticles[index];
    }

    bool hasNext()
    {
        return index < meshRef.mVerticles.size();
    }

    bool operator!=(const Iterator_on_vertices& itOther)
    {
        return index != itOther.index;
    }

    Mesh &meshRef;
    int index;
    Iterator_on_vertices(Mesh &mesh, int index): meshRef(mesh)
    {
        this->index = index;
    }
};



class Circulator_on_faces {
public:
    int getCurrentIndex()
    {
        return index;
    }


    Circulator_on_faces(Mesh &mesh, Vertex &vertex) : meshRef(mesh)
    {
        index = vertex.indexFaceIncident;
        Face &mFace = meshRef.mFaces[index];

        int ind = -1;

        for(int i = 0; i < 3; i++)
            if(meshRef.mVerticles[mFace.vertexIndex[i]] == vertex) ind = i;

        Q_ASSERT(ind != -1 && "crash Circulator_on_faces");
        nextV = mFace.vertexIndex[ind];

        last = index;
    }

    Face& operator*()
    {
        return meshRef.mFaces[index];
    }

    Circulator_on_faces& operator++()
    {
        int nextVId = 0;
        Face &f = meshRef.mFaces[index];
        if(f.vertexIndex[0] == nextV) nextVId = 1;
        else if(f.vertexIndex[1] == nextV) nextVId = 2;
        index = f.adjFaceIndex[nextVId];
        return *this;
    }


    Face* operator->()
    {
        return &meshRef.mFaces[index];
    }

    bool operator!=(const Circulator_on_faces& itOther)
    {
        return index != itOther.index;
    }

    bool hasNext()
    {
        return this->operator++().index != last;
    }

private:
    Mesh &meshRef;
    int index, nextV, last;
};


class Circulator_on_vertices
{
    friend class Mesh;
public:
    int getCurrentIndex()
    {
        return index;
    }

    Vertex& operator*()
    {
        return meshRef.mVerticles[index];
    }

    Circulator_on_vertices& operator++()
    {
        Face &f = meshRef.mFaces.at(faceIndex);
        //trouve face adjacente
        if(f.vertexIndex[0] == index) faceIndex = f.adjFaceIndex[0];
        else if(f.vertexIndex[1] == index) faceIndex = f.adjFaceIndex[1];
        else faceIndex = f.adjFaceIndex[2];

        Face &nf = meshRef.mFaces.at(faceIndex);
        // puis le pivot
        if(nf.vertexIndex[0] == nextV) index = nf.vertexIndex[1];
        else if(nf.vertexIndex[1] == nextV) index = nf.vertexIndex[2];
        else index = nf.vertexIndex[0];
        return *this;
    }

    Vertex* operator->()
    {
        return  &meshRef.mVerticles[index];
    }

    bool operator!=(const Circulator_on_vertices& itOther)
    {
        return index != itOther.index;
    }

    bool hasNext()
    {
        return this->operator++().index != last;
    }



    Circulator_on_vertices(Mesh &mesh, Vertex &vertex): meshRef(mesh)
    {
        faceIndex = vertex.indexFaceIncident;

        Face &mFace = meshRef.mFaces[faceIndex];
        if(meshRef.mVerticles[mFace.vertexIndex[0]] == vertex)
        {
            nextV = mFace.vertexIndex[0];
            index = mFace.vertexIndex[1];
        }
        else if(meshRef.mVerticles[mFace.vertexIndex[1]] == vertex)
        {
            nextV = mFace.vertexIndex[1];
            index = mFace.vertexIndex[2];
        }
        else if(meshRef.mVerticles[mFace.vertexIndex[2]] == vertex)
        {
            nextV = mFace.vertexIndex[2];
            index = mFace.vertexIndex[0];
        }
        else Q_ASSERT("FAIL" && false);
        last = index;
    }


private:
    Mesh &meshRef;
    int nextV, faceIndex, index, last;
};




#endif // CIRCULATEUR_H
