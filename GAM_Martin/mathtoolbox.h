#ifndef MATHTOOLBOX_H
#define MATHTOOLBOX_H

#include <array>
#include <math.h>
#include <QOpenGLWidget>

class Mesh;


class Vec3
{
public:
    Vec3()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    Vec3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float &operator[](int i)
    {

        Q_ASSERT("indice out of bound" && i >= 0 && i < 3);
        if( i == 1) return y;
        if( i == 2) return z;

        return x;
    }

    float operator[](int i) const
    {
        Q_ASSERT("indice out of bound" && i >= 0 && i < 3);
        if( i == 1) return y;
        if( i == 2) return z;

        return x;
    }


    float x;
    float y;
    float z;
};

class Vertex{
public:

    float x;
    float y;
    float z;

    float r;
    float g;
    float b;

    int indexFaceIncident;
    Vertex()
    {
        x = 0; y = 0; z = 0;
        r = 1; g = 1; b = 1;
        indexFaceIncident = -1;
    }
    Vertex(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        r = 1; g = 1; b = 1;
        indexFaceIncident = -1;
    }
    Vertex(float xyz)
    {
        this->x = xyz;
        this->y = xyz;
        this->z = xyz;
        r = 1; g = 1; b = 1;
        indexFaceIncident = -1;
    }
    Vertex(const Vertex &v, int faceId = -1)
    {
        x = v.x; y = v.y; z = v.z;
        r = v.r; g = v.g; b = v.b;

        this->indexFaceIncident = faceId;
    }

    void setRGB(float r, float g, float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    bool operator==(const Vertex &o)
    {
        return x == o.x && y == o.y && z == o.z;
    }


    void set(int i, float val)
    {
        if( i == 0)
            x = val;
        if( i == 1)
            y = val;
        if( i == 2)
            x = val;
    }
    float &operator[](int i)
    {
        return i == 2 ? z : i == 1 ? y : x;
    }

    float operator[](int i) const
    {
        return i == 2 ? z : i == 1 ? y : x;
    }
    bool operator==(const Vertex &vtx) const
    {
        return x == vtx.x
               && y == vtx.y
               && z == vtx.z;
    }

    float length() const
    {
        return sqrt(x*x + y*y + z*z);
    }
    Vertex normalize() const
    {
        float l = (length() != 0);
        assert(l != 0);
        return *this * (1./l);
    }

    Vertex cross(const Vertex &vtx) const
    {
        return Vertex(
            y*vtx.z - z*vtx.y,
            z*vtx.x - x*vtx.z,
            x*vtx.y - y*vtx.x);
    }

    float dot(const Vertex &vtx) const
    {
        return x*vtx.x + y*vtx.y + z*vtx.z;
    }



    float operator*(const Vertex &vtx) const
    {
        return x*vtx.x + y*vtx.y + z*vtx.z;//produit vectoriel *
    }

    Vertex operator+(const Vertex &vtx) const
    {
        return Vertex(x + vtx.x, y+vtx.y, z+vtx.z);
    }


    Vertex operator/(float f) const
    {
        return Vertex(x / f, y / f, z / f);
    }

    Vertex operator-(const Vertex &v) const
    {
        return Vertex(x - v.x, y - v.y, z - v.z);
    }

    Vertex& operator+=(const Vertex &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vertex operator*(float v) const
    {
        return Vertex(x*v, y*v , z*v);
    }


    Vertex operator+(const float v) const
    {
        return Vertex(x+v, y+v , z+v);
    }

    void log(std::string nom="")
    {
        qInfo() << "Vertex " << nom << " => x:" << x << " y:" << y << " z: " << z;
        printf("Vertex(%s) %f %f %f\n", nom.c_str(), x, y, z);
    }
};

class TrioId
{
public:
    TrioId()
    {
        ind[0] = 0;
        ind[1] = 0;
        ind[2] = 0;
    }


    TrioId(int a, int b, int c)
    {
        ind[0] = a;
        ind[1] = b;
        ind[2] = c;
    }

    int &operator[](int i)
    {
        Q_ASSERT("indice out of bound" && i >= 0 && i < 3);
        return ind[i];
    }

    int operator[](int i) const
    {
        Q_ASSERT("indice out of bound" && i >= 0 && i < 3);
        return ind[i];
    }


    TrioId(const TrioId &o)
    {
        memcpy(ind, o.ind, 3*sizeof(int));
    }

    TrioId& operator=(const TrioId& o)
    {
        memcpy(ind, o.ind, 3*sizeof(int));
        return *this;
    }

    int ind[3];
};


#include <cstdlib>   // For std::rand and std::srand
#include <ctime>     // For std::time
#include <random>    // For std::random_device and std::mt19937


template<typename T>
T generateRandomNumber(T min, T max)
{
    static bool srandSet = false;

    if(srandSet == false)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        srandSet = true;
    }

    static std::random_device rd;
    static std::mt19937 mt(rd());

    static std::uniform_real_distribution<> dist(min, max);

    return dist(mt);
}


class Face{
public:

    TrioId vertexIndex; // incident vertex
    TrioId adjFaceIndex; // adjacent face

    Face()
    {

    }

    Face(const TrioId &vertexIndex, const TrioId &adjFaceIndex = TrioId())
    {
        this->vertexIndex = vertexIndex;
        this->adjFaceIndex = adjFaceIndex;
    }

    Face(int a, int b, int c, int d = 0, int e = 0, int f = 0)
    {
        vertexIndex[0] = a;
        vertexIndex[1] = b;
        vertexIndex[2] = c;

        adjFaceIndex[0] = d;
        adjFaceIndex[1] = e;
        adjFaceIndex[2] = f;
    }

    bool infini() const
    {
        return vertexIndex[0] == 0 || vertexIndex[1] == 0 || vertexIndex[2] == 0;
    }

    int findLocalOpposeeId(int face) const
    {
        return adjFaceIndex[0] == face ? 0 :
                adjFaceIndex[1] == face ? 1 :
                adjFaceIndex[2] == face ? 2 : -1;
    }

    int findLocalId(int vertexId) const
    {
        return vertexIndex[0] == vertexId ? 0 :
                   vertexIndex[1] == vertexId ? 1 :
                   vertexIndex[2] == vertexId ? 2 : -1;
    }

    bool has3DifferentVertex() const
    {
        return vertexIndex[1] != vertexIndex[2] &&
               vertexIndex[0] != vertexIndex[1] && vertexIndex[0] != vertexIndex[2];
    }

    static int orientation(Vertex a, Vertex b, Vertex c)
    {
        Vertex vec = (b - a).cross(c - a);

        if(vec.z < 0)
            return -1;
        if(vec.z > 0)
            return 1;

        return 0;
    }
};

#endif // MATHTOOLBOX_H
