#include "headers.h"
#include "libraries.h"
// #include <ft2build.h>
// #include FT_FREETYPE_Hx

void RematchOptionInput(GLFWwindow *window, int &option);


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
  // Material* material = new Material("images/img.jpeg");
  unsigned int shader = make_shaders("shaders/vertex.txt", "shaders/fragment.txt");
  Enviroment *game_env = NULL;
  Player *player = NULL;

  bool isGameOver = false;
  int option = 1;
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    if (option == 1)
    {
      glClearColor(0.0f, 0.9f, 0.0f, 1.0f);
      game_env = new Enviroment();
      player = new Player();
      unsigned int counter = 0;
      unsigned int score = 0;
      isGameOver = false;

      glm::vec3 position(0.f);
      glm::vec3 rotation(0.f);
      glm::vec3 scale(1.f);

      glm::vec3 quad_position = {0.0f, 0.0f, 0.0f};
      glm::vec3 camera_pos = {0.0f, 1.5f, 2.0f};
      glm::vec3 camera_target = {0.0f, 0.0f, 0.0f};
      glm::vec3 up = {0.0f, 0.0f, 1.0f};

      while (!isGameOver)
      {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        game_env->draw(position, rotation, scale, camera_pos, camera_target, up, shader);
        // std::cout << player->translateVec.x << '\n';
        player->handleInput(window, position);
        update_shader(position, rotation, scale, camera_pos, camera_target, up, shader);
        player->draw();

        // std::cout << RoadTriangles.size() << '\n';
        // std::cout << WhiteCrossTriangles.size() << '\n';
        // std::cout << position.y << '\n';
        // deleting the first triangle
        // std::cout << game_env->Walls.size() << '\n';

        
        isGameOver = game_env->collide_with_wall(player);
        if(game_env->collide_with_coin(player)){
           std::cout << " + 10 " << '\n';
           score += 10;
        }
        game_env->update_enviroment(counter, position);
        glfwSwapBuffers(window);
        counter += 1;
      }
      std::cout << "Game Over" << '\n';
      std::cout << "Your Score : " << score << '\n';
      game_env->~Enviroment();
      player->~Player();
      game_env = NULL;
      player = NULL;
    }
    else if(option == 2)
    {
      break;
    }
    // delete triangle1;
    // delete triangle2;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    RematchOptionInput(window, option);
    // while(1){
    //   glfwPollEvents();
    //   glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    // }
  }
  if (game_env != NULL)
  {
    game_env->~Enviroment();
    player->~Player();
  }
  glDeleteProgram(shader);
  glfwTerminate();
  return 0;
}

void RematchOptionInput(GLFWwindow *window, int &option)
{
  if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
  {
    option = 1;
  }
  else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
  {
    option = 2;
  }
  else
  {
    option = 0;
  }
}