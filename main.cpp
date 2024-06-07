#include "headers.h"
#include "libraries.h"

// #define STB_IMAGE_IMPLEMENTATION
#define WHITE_CROSS_INTERVAL 0.20f
#define STEP_SIZE 0.01f

void update_enviroment(std::vector<TriangleMesh *> &Triangles, int &counter, glm::vec3 &position);
void UpdateShader(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 camera_pos,
                  glm::vec3 camera_target, glm::vec3 up, unsigned int &shader);
void handlePlayerInput(GLFWwindow* window, glm::vec3& position,  TriangleMesh* player);

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
  // glViewport(450, 450, 200, 200);

  glClearColor(0.0f, 0.9f, 0.0f, 1.0f);

  // Material* material = new Material("images/img.jpeg");
  unsigned int shader = make_shaders("shaders/vertex.txt", "shaders/fragment.txt");

  // glUseProgram(shader);

  std::vector<TriangleMesh *> RoadTriangles;
  std::vector<TriangleMesh *> WhiteCrossTriangles;

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

    RoadTriangles.push_back(new TriangleMesh(positions1, 3));

    positions2[1] = i - STEP_SIZE;
    positions2[4] = i - STEP_SIZE;
    positions2[7] = i;
    RoadTriangles.push_back(new TriangleMesh(positions2, 3));
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

      WhiteCrossTriangles.push_back(new TriangleMesh(whiteTriPos[j], 5));
    }
  }

  Player* player = new Player();
  int counter = 0;

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

    position.y = 0.0f;
    UpdateShader(position, rotation, scale, camera_pos, camera_target, up, shader);
    for (auto triangle : RoadTriangles)
    {
      triangle->draw();
    }
    
    for (auto triangle : WhiteCrossTriangles)
    {
      position = triangle->translateVec;
      UpdateShader(position, rotation, scale, camera_pos, camera_target, up, shader);
      triangle->draw();
      triangle->translateVec.y += STEP_SIZE;
    }

    // std::cout << player->translateVec.x << '\n';
    player->handleInput(window, position);
    UpdateShader(position, rotation, scale, camera_pos, camera_target, up, shader);
    player->draw();


    // std::cout << RoadTriangles.size() << '\n';
    // std::cout << WhiteCrossTriangles.size() << '\n';
    // std::cout << position.y << '\n';
    // deleting the first triangle
    update_enviroment(WhiteCrossTriangles, counter, position);
    glfwSwapBuffers(window);
    counter += 1;
  }
  // delete triangle1;
  // delete triangle2;
  glDeleteProgram(shader);
  glfwTerminate();
  return 0;
}
void update_enviroment(std::vector<TriangleMesh *> &Triangles, int &counter, glm::vec3 &position)
{

  if (counter == 60)
  {
    for (int i = 0; i < 4; i++)
    {
      if (!Triangles.empty())
      {
        delete Triangles.front();
        Triangles.erase(Triangles.begin());
      }
      else
      {
        break;
      }
    }

    Triangles.push_back(new TriangleMesh(
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
      4));

    Triangles.push_back(new TriangleMesh(
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
      4));
    Triangles.push_back(new TriangleMesh(
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
      4));

    Triangles.push_back(new TriangleMesh(
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
      4));
    counter = 0;
  }
}

void UpdateShader(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 camera_pos,
                  glm::vec3 camera_target, glm::vec3 up, unsigned int &shader)
{
  glm::mat4 ModelMatrix(1.f);
  ModelMatrix = glm::translate(ModelMatrix, position);
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
  ModelMatrix = glm::scale(ModelMatrix, scale);

  glm::mat4 view = glm::lookAt(camera_pos, camera_target, up);
  glm::mat4 projection = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 10.0f);

  glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
  glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

  glUseProgram(shader);
}


// void update_enviroment(std::vector<TriangleMesh *> &Triangles, int &counter, glm::vec3 &position)
// {

//   if (counter == 100)
//   {
//     for (int i = 0; i < 6; i++)
//     {
//       if (!Triangles.empty())
//       {
//         delete Triangles.front();
//         Triangles.erase(Triangles.begin());
//       }
//       else
//       {
//         break;
//       }
//     }

//     Triangles.push_back(new TriangleMesh(
//       {
//         0.350f,
//         -3.0f - position.y,
//         0.0f,
//         0.350f,
//         -(3.0f - WHITE_CROSS_INTERVAL) - position.y,
//         0.0f,
//         0.325f,
//         -(3.0f - WHITE_CROSS_INTERVAL) - position.y,
//         0.0f,
//       },
//       4));

//     Triangles.push_back(new TriangleMesh(
//       {
//         0.350f,
//         -3.0f - position.y,
//         0.0f,
//         0.325f,
//         -3.0f - position.y,
//         0.0f,
//         0.325f,
//         -(3.0f - WHITE_CROSS_INTERVAL) - position.y,
//         0.0f,
//       },
//       4));
//     Triangles.push_back(new TriangleMesh(
//       {
//         -0.350f,
//         -3.0f - position.y,
//         0.0f,
//         -0.350f,
//         -(3.0f - WHITE_CROSS_INTERVAL) - position.y,
//         0.0f,
//         -0.325f,
//         -(3.0f - WHITE_CROSS_INTERVAL) - position.y,
//         0.0f,
//       },
//       4));

//     Triangles.push_back(new TriangleMesh(
//       {
//         -0.350f,
//         -3.0f - position.y,
//         0.0f,
//         -0.325f,
//         -3.0f - position.y,
//         0.0f,
//         -0.325f,
//         -(3.0f - WHITE_CROSS_INTERVAL) - position.y,
//         0.0f,
//       },
//       4));

//     Triangles.push_back(new TriangleMesh({-1.0f, -3.0f - position.y, 0.0f, 1.0f, -(3.0f - STEP_SIZE) - position.y,
//     0.0f,
//                                           -1.0f, -(3.0f - STEP_SIZE) - position.y, 0.0f},
//                                          3));

//     Triangles.push_back(new TriangleMesh(
//       {1.0f, -(3.0f - STEP_SIZE) - position.y, 0.0f, 1.0f, -3.0f - position.y, 0.0f, -1.0f, -3.0f - position.y,
//       0.0f}, 3));
//     counter = 0;
//   }
//   else
//   {
//     for (int i = 0; i < 2; i++)
//     {
//       if (!Triangles.empty())
//       {
//         delete Triangles.front();
//         Triangles.erase(Triangles.begin());
//       }
//       else
//       {
//         break;
//       }
//     }
//     Triangles.push_back(new TriangleMesh({-1.0f, -3.0f - position.y, 0.0f, 1.0f, -(3.0f - STEP_SIZE) - position.y,
//     0.0f,
//                                           -1.0f, -(3.0f - STEP_SIZE) - position.y, 0.0f},
//                                          3));

//     Triangles.push_back(new TriangleMesh(
//       {1.0f, -(3.0f - STEP_SIZE) - position.y, 0.0f, 1.0f, -3.0f - position.y, 0.0f, -1.0f, -3.0f - position.y,
//       0.0f}, 3));
//   }
// }