#if !defined(__WALL_H__)
#define __WALL_H__

#include "libraries.h"
#include "triangle_mesh.h"
#include "player.h"

class Wall
{
public:
  std::vector<TriangleMesh *> WallTriangles;
  glm::vec3 TranslateVec;
  unsigned int lane;
  Wall();
  void draw(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale, glm::vec3 &camera_pos, glm::vec3 &camera_target,
            glm::vec3 &up, unsigned int &shader);
  bool is_player_collide(Player* player);
  ~Wall();
private:
  unsigned int generateRandomLane();
  void changeLane(glm::vec3 &translateVec, unsigned int new_lane);
};

#endif // __WALL_H__
