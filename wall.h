#if !defined(__WALL_H__)
#define __WALL_H__

#include "libraries.h"
#include "triangle_mesh.h"

class Wall
{
public:
  TriangleMesh *triangle1;
  TriangleMesh *triangle2;
  glm::vec3 TranslateVec;
  Wall();
  void draw();
  ~Wall();
};

#endif // __WALL_H__
