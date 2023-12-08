#ifndef SCENE_H
#define SCENE_H

#include "mathtoolbox.h"
#include "mesh.h"
#include "laplacien.h"
#include "draw.h"

#include <vector>

class Scene //Generally used to create a singleton instance
{
public :
  Scene();


  void reset(bool dim2);
  void Load2Dpoints(std::string name);
  void load3DModel(std::string name);

  void draw();
  void drawAxis();

  Mesh mMesh;

};
#endif // SCENE_H
