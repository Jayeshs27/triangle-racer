#if !defined(__MAP_H__)
#define __MAP_H__

#include "libraries.h"
#include "triangle_mesh.h"
#include "wall.h"
#include "player.h"

class Enviroment
{
public:
  std::vector<TriangleMesh *> RoadTriangles;
  std::vector<TriangleMesh *> WhiteCrossTriangles;
  std::vector<Wall*> Walls;
  std::vector<int> not_required_walls;

  Enviroment();
  void draw(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale, glm::vec3 &camera_pos, glm::vec3 &camera_target,
            glm::vec3 &up, unsigned int &shader);
  void update_enviroment(unsigned int &counter, glm::vec3 &position);
  bool collide_with_wall(Player* player);
  ~Enviroment();
};

#endif // __MAP_H__
