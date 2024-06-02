#include "headers.h"
#include "libraries.h"

// #define STB_IMAGE_IMPLEMENTATION

int main()  {
    GLFWwindow* window;

    if(!glfwInit()) {
        std::cout << "GLFW couldn't start" << std::endl;
        return -1;  
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(500, 500, "Game Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Could not load opengl" << '\n';
        glfwTerminate();
        return -1;
    }
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    // glViewport(450, 450, 200, 200);

    glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
     
    TriangleMesh* triangle = new TriangleMesh();
    Material* material = new Material("images/img.jpeg");
    unsigned int shader = make_shaders(
        "shaders/vertex.txt",
        "shaders/fragment.txt"
    );

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);
        triangle->draw();
        material->use();

        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader);
    delete triangle;
    glfwTerminate();
    return 0;
}


