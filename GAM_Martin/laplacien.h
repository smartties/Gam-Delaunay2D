#ifndef LAPLACIEN_H
#define LAPLACIEN_H

#include "mesh.h"
#include <vector>

namespace Laplacien
{

    #define COMPUTE_LAPLACIEN_X 0x1
    #define COMPUTE_LAPLACIEN_Y 0x2
    #define COMPUTE_LAPLACIEN_Z 0x4
    #define COMPUTE_COURBURE    0x8

    Vec3 courburetoHSVtoRGB(float val);

    float aireAutourDe(Mesh &mesh,int ind);

    void computeLaplacienMesh(Mesh &mesh, int flag = COMPUTE_COURBURE);

};


#endif // LAPLACIEN_H
