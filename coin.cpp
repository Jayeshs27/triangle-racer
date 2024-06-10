#include "coin.h"

Coin::Coin(unsigned int lane)
{
  radius = 0.1f;
  this->lane = lane;
  translateVec = {0.0f, 0.0f, 0.0f};
  std::vector<float> center = {0.0f, -3.0f, 1.0f};
  unsigned int num_triangles = 90;
  float theta = 2 * M_PI / num_triangles;
  std::vector<float> cirTriangle(9);

  cirTriangle[0] = center[0];
  cirTriangle[1] = center[1];
  cirTriangle[2] = center[2];

  cirTriangle[3] = center[0];
  cirTriangle[4] = center[1];
  cirTriangle[5] = center[2] - radius * (float)cos(theta);

  cirTriangle[6] = center[0] - radius * (float)sin(theta);
  cirTriangle[7] = center[1];
  cirTriangle[8] = center[2] - radius * (float)cos(theta);

  CoinTriangles.push_back(new TriangleMesh(cirTriangle, YELLOW));

  for (int i = 2; i <= num_triangles; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      cirTriangle[3 + j] = cirTriangle[6 + j];
    }
    float act_theta  = theta * i;
    cirTriangle[6] = center[0] - radius * sin(act_theta);
    cirTriangle[8] = center[2] - radius * cos(act_theta);
    CoinTriangles.push_back(new TriangleMesh(cirTriangle, YELLOW));
  }
  std::vector<float> triangle1Pos = {
    0.20, 1.0f, 0.5f, -0.20f, 1.0f, 0.5f, -0.20f, 1.0f, 1.0f,
  };
  changeLane(lane);
//   CoinTriangles.push_back(new TriangleMesh(triangle1Pos, YELLOW));
}

void Coin::draw(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale, glm::vec3 &camera_pos,
                glm::vec3 &camera_target, glm::vec3 &up, unsigned int &shader)
{
  position = translateVec;
  update_shader(position, rotation, scale, camera_pos, camera_target, up, shader);
  for (auto triangle : CoinTriangles)
  {
    triangle->draw();
  }
}
void Coin::changeLane(unsigned int lane){
   switch(lane) {
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

bool Coin::is_player_collide(Player* player){
  // std::cout << translateVec.y << " " << lane << " " << player->lane << '\n';
  if(translateVec.y >= 3.74f && translateVec.y <= 3.76f && player->lane == lane){
    return true;
  }
  return false;
}

Coin::~Coin()
{
    for(auto triangle : CoinTriangles)
    {
        delete triangle;
    }
    CoinTriangles.clear();
}