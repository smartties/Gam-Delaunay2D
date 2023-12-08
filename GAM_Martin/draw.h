#ifndef DRAW_H
#define DRAW_H

#include "mesh.h"

class Draw
{

public:
    friend class Mesh;
    static void render(Mesh &mesh, int flag);


    static int typeRender;
};

#endif // DRAW_H
