#if !defined(__MAP_H__)
#define __MAP_H__

#include "libraries.h"
#include "triangle_mesh.h"

class Enviroment
{
public:
  std::vector<TriangleMesh *> RoadTriangles;
  std::vector<TriangleMesh *> WhiteCrossTriangles;
  Enviroment();
  void draw(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale, glm::vec3 &camera_pos, glm::vec3 &camera_target,
            glm::vec3 &up, unsigned int &shader);
  void update_enviroment(unsigned int &counter, glm::vec3 &position);
  ~Enviroment();
};

#endif // __MAP_H__
