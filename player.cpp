#include "player.h"

Player::Player()
{

  std::vector<float> playerPos{
    0.15f, 1.0f, 0.5f, -0.15f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f,
  };
  lane = 2;
  translateVec = {0.0f, 0.0f, 0.0f};
  triangle = new TriangleMesh(playerPos, 2);
}

void Player::draw()
{
  triangle->draw();
}

void Player::goRight()
{
  if (lane != 1)
  {
    lane -= 1;
    translateVec.x -= 0.5f;
  }
}
void Player::goLeft()
{
  if (lane != 3)
  {
    lane += 1;
    translateVec.x += 0.5f;
  }
}

void Player::handleInput(GLFWwindow* window, glm::vec3& position)
{
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
  {
    goRight();
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
  {
    goLeft();
  }
  position = translateVec;
}


Player::~Player()
{
  triangle->~TriangleMesh();
}