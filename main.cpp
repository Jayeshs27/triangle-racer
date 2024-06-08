#include "headers.h"
#include "libraries.h"

int main()
{
  GLFWwindow *window;

  if (!glfwInit())
  {
    std::cout << "GLFW couldn't start" << std::endl;
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

  window = glfwCreateWindow(800, 500, "Game Window", NULL, NULL);
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Could not load opengl" << '\n';
    glfwTerminate();
    return -1;
  }
  int w, h;
  glfwGetFramebufferSize(window, &w, &h);
  glClearColor(0.0f, 0.9f, 0.0f, 1.0f);

  // Material* material = new Material("images/img.jpeg");
  unsigned int shader = make_shaders("shaders/vertex.txt", "shaders/fragment.txt");
  
  // while(1){
    Enviroment* game_env = new Enviroment();
    Player* player = new Player();
    unsigned int counter = 0;

    glm::vec3 position(0.f);
    glm::vec3 rotation(0.f);
    glm::vec3 scale(1.f);

    glm::vec3 quad_position = {0.0f, 0.0f, 0.0f};
    glm::vec3 camera_pos = {0.0f, 1.5f, 2.0f};
    glm::vec3 camera_target = {0.0f, 0.0f, 0.0f};
    glm::vec3 up = {0.0f, 0.0f, 1.0f};

    while (!glfwWindowShouldClose(window))
    {
      glfwPollEvents();
      glClear(GL_COLOR_BUFFER_BIT);

      game_env->draw(position, rotation, scale, camera_pos, camera_target,
      up, shader);
      // std::cout << player->translateVec.x << '\n';
      player->handleInput(window, position);
      update_shader(position, rotation, scale, camera_pos, camera_target, up, shader);
      player->draw();

      // std::cout << RoadTriangles.size() << '\n';
      // std::cout << WhiteCrossTriangles.size() << '\n';
      // std::cout << position.y << '\n';
      // deleting the first triangle
      // std::cout << game_env->Walls.size() << '\n';
      game_env->collide_with_wall(player);
      game_env->update_enviroment(counter, position);
      glfwSwapBuffers(window);
      counter += 1;
    }
    // delete triangle1;
    // delete triangle2;
    game_env->~Enviroment();
    player->~Player();
    glDeleteProgram(shader);
    glfwTerminate();

    // break;
  // }
  return 0;
}


