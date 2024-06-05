#include "headers.h"
#include "libraries.h"

// #define STB_IMAGE_IMPLEMENTATION

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

  std::vector<TriangleMesh *> Triangles;
  // Material* material = new Material("images/img.jpeg");
  unsigned int shader = make_shaders("shaders/vertex.txt", "shaders/fragment.txt");

  glUseProgram(shader);

  // std::vector<float> positions = {
  //      1.0f,  1.0f, 0.0f,
  //      1.0f, -1.0f, 0.0f,
  //     -1.0f,  1.0f, 0.0f,
  // };
  // TriangleMesh* triangle1 = new new TriangleMesh(
  //     {
  //      1.0f,  2.0f, 0.0f,
  //      1.0f, -3.0f, 0.0f,
  //     -1.0f,  2.0f, 0.0f,
  //     },   3);
  // Triangles.push_back(triangle1);
  // TriangleMesh* triangle2 = new new TriangleMesh(
  //     {
  //      -1.0f,  -3.0f, 0.0f,
  //      1.0f, -3.0f, 0.0f,
  //     -1.0f,  2.0f, 0.0f,
  //     },   3);
  // Triangles.push_back(triangle2);
  float STEP_SIZE = 0.01;
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

    Triangles.push_back(new TriangleMesh(positions1, 3));

    positions2[1] = i - STEP_SIZE;
    positions2[4] = i - STEP_SIZE;
    positions2[7] = i;
    Triangles.push_back(new TriangleMesh(positions2, 3));
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
  float WHITE_CROSS_INTERVAL = 0.25;
  for (float i = 0.0f; i > -3.0f; i -= 0.125)
  {
    for (int j = 0; j < 4; j++)
    {
      whiteTriPos[j][1] += i;
      whiteTriPos[j][4] += i;
      whiteTriPos[j][7] += i;

      Triangles.push_back(new TriangleMesh(whiteTriPos[j], 4));
    }
  }

  // glClear(GL_COLOR_BUFFER_BIT);
  // glUseProgram(shader);
  // triangle->draw();
  // glfwSwapBuffers(window);
  // Triangles.push_back(
  //     new TriangleMesh({
  //      1.0f,  1.0f, 0.0f,
  //      1.0f, -1.0f, 0.0f,
  //     -1.0f,  1.0f, 0.0f,
  // }, 3));

  // Triangles.push_back(
  //     new TriangleMesh({
  //      -1.0f,  -1.0f, 0.0f,
  //      1.0f, -1.0f, 0.0f,
  //     -1.0f,  1.0f, 0.0f,
  // }, 3));

  glm::vec3 position(0.f);
  glm::vec3 rotation(0.f);
  glm::vec3 scale(1.f);

  glm::mat4 ModelMatrix(1.f);
  ModelMatrix = glm::translate(ModelMatrix, position);
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
  ModelMatrix = glm::scale(ModelMatrix, scale);

  glm::vec3 quad_position = {0.0f, 0.0f, 0.0f};
  glm::vec3 camera_pos = {0.0f, 1.5f, 2.0f};
  glm::vec3 camera_target = {0.0f, 0.0f, 0.0f};
  glm::vec3 up = {0.0f, 0.0f, 1.0f};

  glm::mat4 view = glm::lookAt(camera_pos, camera_target, up);
  glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));

  glm::mat4 projection = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 10.0f);
  glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

  int counter = 0;

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    // if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
    //     std::cout << "key down pressed" << '\n';
    // }
    // glm::mat4 model = glm::mat4(1.0f);
    // model = glm::translate(model, quad_position);
    // model = glm::rotate(model, (float)glfwGetTime(), up);
    // rotation.z += 0.1f;
    // if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
    //     position.z += STEP_SIZE;
    // }
    // if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
    //     position.z -= STEP_SIZE;
    // }

    // rotation.x += 0.3f;
    // rotation.y += 0.3f;

    position.y += STEP_SIZE;

    ModelMatrix = glm::mat4(1.f);
    ModelMatrix = glm::translate(ModelMatrix, position);
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
    ModelMatrix = glm::scale(ModelMatrix, scale);

    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);

    for (auto triangle : Triangles)
    {
      triangle->draw();
    }
    std::cout << Triangles.size() << '\n';
    // deleting the first triangles

    if (counter == 100)
    {
      for (int i = 0; i < 6; i++)
      {
        if (!Triangles.empty())
        {
          delete Triangles.front();
          Triangles.erase(Triangles.begin());
        }
      }

      Triangles.push_back(new TriangleMesh(
        {
          0.350f,
          -3.0f - position.y,
          0.0f,
          0.350f,
          -(3.0f - WHITE_CROSS_INTERVAL) - position.y,
          0.0f,
          0.325f,
          -(3.0f - WHITE_CROSS_INTERVAL) - position.y,
          0.0f,
        },
      4));

      Triangles.push_back(new TriangleMesh(
        {
          0.350f,
          -3.0f - position.y,
          0.0f,
          0.325f,
          -3.0f - position.y,
          0.0f,
          0.325f,
          -(3.0f - WHITE_CROSS_INTERVAL) - position.y,
          0.0f,
        },
      4));
      Triangles.push_back(new TriangleMesh(
        {
          -0.350f,
          -3.0f - position.y,
          0.0f,
          -0.350f,
          -(3.0f - WHITE_CROSS_INTERVAL) - position.y,
          0.0f,
          -0.325f,
          -(3.0f - WHITE_CROSS_INTERVAL) - position.y,
          0.0f,
        },
      4));

      Triangles.push_back(new TriangleMesh(
        {
          -0.350f,
          -3.0f - position.y,
          0.0f,
          -0.325f,
          -3.0f - position.y,
          0.0f,
          -0.325f,
          -(3.0f - WHITE_CROSS_INTERVAL) - position.y,
          0.0f,
        },
      4));

      Triangles.push_back(new TriangleMesh({-1.0f, -3.0f - position.y, 0.0f, 1.0f, -(3.0f - STEP_SIZE) - position.y, 0.0f,
                                            -1.0f, -(3.0f - STEP_SIZE) - position.y, 0.0f},
                                          3));

      Triangles.push_back(new TriangleMesh(
        {1.0f, -(3.0f - STEP_SIZE) - position.y, 0.0f, 1.0f, -3.0f - position.y, 0.0f, -1.0f, -3.0f - position.y, 0.0f},
        3));
      counter = 0;
    }
    else{
      for (int i = 0; i < 2; i++)
      {
        if (!Triangles.empty())
        {
          delete Triangles.front();
          Triangles.erase(Triangles.begin());
        }
      }
      Triangles.push_back(new TriangleMesh({-1.0f, -3.0f - position.y, 0.0f, 1.0f, -(3.0f - STEP_SIZE) - position.y, 0.0f,
                                            -1.0f, -(3.0f - STEP_SIZE) - position.y, 0.0f},
                                          3));

      Triangles.push_back(new TriangleMesh(
        {1.0f, -(3.0f - STEP_SIZE) - position.y, 0.0f, 1.0f, -3.0f - position.y, 0.0f, -1.0f, -3.0f - position.y, 0.0f},
        3));
    }



    glfwSwapBuffers(window);
    counter += 1;
  }
  // delete triangle1;
  // delete triangle2;
  glDeleteProgram(shader);
  glfwTerminate();
  return 0;
}
