#include "map.h"
#include "color.h"
#include "shaders.h"

#define WHITE_CROSS_INTERVAL 0.20f
#define STEP_SIZE 0.01f

Enviroment::Enviroment()
{
  std::vector<float> positions1 = {
    1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, -1.0f, 1.0f, 0.0f,
  };

  std::vector<float> positions2 = {
    -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, -1.0f, 1.0f, 0.0f,
  };

  for (float i = 2.0; i >= -(3.0 - STEP_SIZE); i -= STEP_SIZE)
  {
    positions1[1] = i;
    positions1[4] = i - STEP_SIZE;
    positions1[7] = i;

    RoadTriangles.push_back(new TriangleMesh(positions1, GREY));

    positions2[1] = i - STEP_SIZE;
    positions2[4] = i - STEP_SIZE;
    positions2[7] = i;
    RoadTriangles.push_back(new TriangleMesh(positions2, GREY));
  }

  std::vector<float> whiteTriPos[4] = {
    {
      0.350f,
      1.75f,
      0.0f,
      0.350f,
      2.0f,
      0.0f,
      0.325f,
      2.0f,
      0.0f,
    },
    {
      0.350f,
      1.75f,
      0.0f,
      0.325f,
      1.75f,
      0.0f,
      0.325f,
      2.0f,
      0.0f,
    },
    {
      -0.350f,
      1.75f,
      0.0f,
      -0.350f,
      2.0f,
      0.0f,
      -0.325f,
      2.0f,
      0.0f,
    },
    {
      -0.350f,
      1.75f,
      0.0f,
      -0.325f,
      1.75f,
      0.0f,
      -0.325f,
      2.0f,
      0.0f,
    },
  };

  for (float i = 0.0f; i > -1.5f; i -= 0.20f)
  {
    for (int j = 0; j < 4; j++)
    {
      whiteTriPos[j][1] += i;
      whiteTriPos[j][4] += i;
      whiteTriPos[j][7] += i;

      WhiteCrossTriangles.push_back(new TriangleMesh(whiteTriPos[j], WHITE));
    }
  }
}
void Enviroment::draw(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale, glm::vec3 &camera_pos,
                      glm::vec3 &camera_target, glm::vec3 &up, unsigned int &shader)
{
  position = {0.0f, 0.0f, 0.0f};
  update_shader(position, rotation, scale, camera_pos, camera_target, up, shader);
  for (auto triangle : RoadTriangles)
  {
    triangle->draw();
  }

  for (auto triangle : WhiteCrossTriangles)
  {
    position = triangle->translateVec;
    update_shader(position, rotation, scale, camera_pos, camera_target, up, shader);
    triangle->draw();
    triangle->translateVec.y += STEP_SIZE;
  }

  int i = 0;
  for (auto wall : Walls)
  {
    wall->draw(position, rotation, scale, camera_pos, camera_target, up, shader);
    wall->TranslateVec.y += STEP_SIZE;
    if (wall->TranslateVec.y > 5.0)
    {
      not_required_walls.push_back(i);
    }
    i += 1;
    // std::cout << wall->TranslateVec << '\n';
  }
}
void Enviroment::update_enviroment(unsigned int &counter, glm::vec3 &position)
{

  for (auto index : not_required_walls)
  {
    delete Walls[index];
  }
  int offset = 0;
  for (auto index : not_required_walls)
  {
    Walls.erase(Walls.begin() + index - offset);
    offset += 1;
  }

  not_required_walls.clear();

  if (counter == 60)
  {
    for (int i = 0; i < 4; i++)
    {
      if (!WhiteCrossTriangles.empty())
      {
        delete WhiteCrossTriangles.front();
        WhiteCrossTriangles.erase(WhiteCrossTriangles.begin());
      }
      else
      {
        break;
      }
    }

    WhiteCrossTriangles.push_back(new TriangleMesh(
      {
        0.350f,
        -3.0f,
        0.0f,
        0.350f,
        -(3.0f - WHITE_CROSS_INTERVAL),
        0.0f,
        0.325f,
        -(3.0f - WHITE_CROSS_INTERVAL),
        0.0f,
      },
      WHITE));

    WhiteCrossTriangles.push_back(new TriangleMesh(
      {
        0.350f,
        -3.0f,
        0.0f,
        0.325f,
        -3.0f,
        0.0f,
        0.325f,
        -(3.0f - WHITE_CROSS_INTERVAL),
        0.0f,
      },
      WHITE));

    WhiteCrossTriangles.push_back(new TriangleMesh(
      {
        -0.350f,
        -3.0f,
        0.0f,
        -0.350f,
        -(3.0f - WHITE_CROSS_INTERVAL),
        0.0f,
        -0.325f,
        -(3.0f - WHITE_CROSS_INTERVAL),
        0.0f,
      },
      WHITE));

    WhiteCrossTriangles.push_back(new TriangleMesh(
      {
        -0.350f,
        -3.0f,
        0.0f,
        -0.325f,
        -3.0f,
        0.0f,
        -0.325f,
        -(3.0f - WHITE_CROSS_INTERVAL),
        0.0f,
      },
      WHITE));

    Walls.push_back(new Wall());
    counter = 0;
  }
}

bool Enviroment::collide_with_wall(Player *player)
{
  for (auto wall : Walls)
  {
    if(wall->is_player_collide(player)){
      std::cout << "Game over" << '\n';
      return true;
    }
  }
  return false;
}

Enviroment::~Enviroment()
{
  for (auto Triangle : RoadTriangles)
  {
    delete Triangle;
  }
  for (auto Triangle : WhiteCrossTriangles)
  {
    delete Triangle;
  }
  for (auto wall : Walls)
  {
    wall->~Wall();
  }
  RoadTriangles.clear();
  WhiteCrossTriangles.clear();
  Walls.clear();
}