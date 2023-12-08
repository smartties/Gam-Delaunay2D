#include "draw.h"



int Draw::typeRender = 0;

void Draw::render(Mesh &mesh, int flag)
{
    bool drawTri = typeRender == 0; //mesh.hasPointinfini == false;

    glColor3f(1.f, 1.f, 1.f);
    if(drawTri)
        glBegin(GL_TRIANGLES);
    else
        glBegin(GL_LINES);

    for(int i = 0; i < mesh.mFaces.size(); i++)
    {
        Face &face = mesh.mFaces[i];

        if(drawTri == false)
        {
            if(face.has3DifferentVertex()) glColor3f(1.f, 1.f, 1.f);
            else glColor3f(1.f, 0.f, 0.f);

            for(int j = 0; j < 3; j++)
            {
                if(mesh.mVerticles[face.vertexIndex[(j+0)%3]].z != 0 || mesh.mVerticles[face.vertexIndex[(j+1)%3]].z != 0)
                    glColor3f(1.f, 0.f, 0.f);
                else
                    glColor3f(1.f, 1.f, 1.f);

                glVertex3f(mesh.mVerticles[face.vertexIndex[(j+0)%3]].x, mesh.mVerticles[face.vertexIndex[(j+0)%3]].y, mesh.mVerticles[face.vertexIndex[(j+0)%3]].z);
                glVertex3f(mesh.mVerticles[face.vertexIndex[(j+1)%3]].x, mesh.mVerticles[face.vertexIndex[(j+1)%3]].y, mesh.mVerticles[face.vertexIndex[(j+1)%3]].z);
            }
        }
        else // triangle
        {
            if(face.infini() == false || mesh.hasPointinfini == false)
            {
            glColor3d(mesh.mVerticles[face.vertexIndex[0]].r, mesh.mVerticles[face.vertexIndex[0]].g, mesh.mVerticles[face.vertexIndex[0]].b);
            glVertex3f(mesh.mVerticles[face.vertexIndex[0]].x, mesh.mVerticles[face.vertexIndex[0]].y, mesh.mVerticles[face.vertexIndex[0]].z);
            glColor3d(mesh.mVerticles[face.vertexIndex[1]].r, mesh.mVerticles[face.vertexIndex[1]].g, mesh.mVerticles[face.vertexIndex[1]].b);
            glVertex3f(mesh.mVerticles[face.vertexIndex[1]].x, mesh.mVerticles[face.vertexIndex[1]].y, mesh.mVerticles[face.vertexIndex[1]].z);
            glColor3d(mesh.mVerticles[face.vertexIndex[2]].r, mesh.mVerticles[face.vertexIndex[2]].g, mesh.mVerticles[face.vertexIndex[2]].b);
            glVertex3f(mesh.mVerticles[face.vertexIndex[2]].x, mesh.mVerticles[face.vertexIndex[2]].y, mesh.mVerticles[face.vertexIndex[2]].z);
            }
        }
    }
    glEnd();
}

