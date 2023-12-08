#include "scene.h"

Scene::Scene()
{
    mMesh.reset();
    mMesh.makeTetraedre(1);
    mMesh.setPointInfini(true);
}




void Scene::reset(bool dim2)
{
    mMesh.reset();
    mMesh.makeTetraedre(1);
    mMesh.setPointInfini(dim2);
}

void Scene::Load2Dpoints(std::string name)
{
    bool success = false;
    if( name != "none")
    {
        printf("Load2Dpoints\n");
        mMesh.reset();
        mMesh.makeTetraedre(0.01);
        success = mMesh.loadPointsTxt(name);
    }

    if(success == false)
    {
        mMesh.reset();
        mMesh.makeTetraedre(1);
        mMesh.setPointInfini(true);
    }
}
void Scene::load3DModel(std::string name)
{
    mMesh.reset();

    mMesh.setPointInfini(false);
    bool success = mMesh.loadMeshOff(name);
    printf("success load %d\n", success);
    if(success == false)
    {
        mMesh.reset();
        mMesh.makeTetraedre(1);
    }

    mMesh.generateTopology();
}

void Scene::draw()
{
    if(mMesh.hasPointinfini)
        Draw::render(mMesh, 0x2);
    else
        Draw::render(mMesh, 0x1);
}

void Scene::drawAxis()
{

    glBegin(GL_LINES);
    glColor3d(0,1,0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3d(1,0,0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3d(0,0,1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();
}


