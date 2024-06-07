#if !defined(__PLAYER_H__)
#define __PLAYER_H__

#include "libraries.h"
#include "triangle_mesh.h"


class Player
{
public:
glm::vec3 translateVec;
TriangleMesh* triangle;
int lane;
Player();
void draw();
void goRight();
void goLeft();
void handleInput(GLFWwindow* window, glm::vec3& position);
~Player();
private:

};

#endif // __PLAYER_H__
