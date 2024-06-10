#include "wall.h"
#include "color.h"
#include "shaders.h"

Wall::Wall()
{

  std::vector<float> triangle1Pos = {
    0.20, -3.0f, 0.5f, -0.20f, -3.0f, 0.5f, -0.20f, -3.0f, 1.0f,
  };
  std::vector<float> triangle2Pos = {
    0.20, -3.0f, 0.5f, 0.20f, -3.0f, 1.0f, -0.20f, -3.0f, 1.0f,
  };

  WallTriangles.push_back(new TriangleMesh(triangle1Pos, BLACK));
  WallTriangles.push_back(new TriangleMesh(triangle2Pos, BLACK));

  TranslateVec = {0.0f, 0.0f, 0.0f};
  lane = generateRandomLane();
  changeLane(TranslateVec, lane);
}

void Wall::draw(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale, glm::vec3 &camera_pos,
                glm::vec3 &camera_target, glm::vec3 &up, unsigned int &shader)
{
  position = TranslateVec;
  update_shader(position, rotation, scale, camera_pos, camera_target, up, shader);

  for (auto triangle : WallTriangles)
  {
    triangle->draw();
  }
}

unsigned int Wall::generateRandomLane()
{
  return ((rand() % 3) + 1);
}

void Wall::changeLane(glm::vec3 &translateVec, unsigned int new_lane)
{
  switch(new_lane) {
    case 1:
      translateVec.x = 0.675;
      return;
    case 2:
      return;
    case 3:
      translateVec.x = -0.675;
      return;
  }
}

bool Wall::is_player_collide(Player* player){
  if(TranslateVec.y >= 3.74f && TranslateVec.y <= 3.76f && player->lane == lane){
    return true;
  }
  return false;
}

Wall::~Wall()
{
  for (auto triangle : WallTriangles)
  {
    delete triangle;
  }
  WallTriangles.clear();
}