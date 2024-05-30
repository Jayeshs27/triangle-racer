#include "headers.h"

int main()  {
    GLFWwindow* window;

    // std::ifstream file;
    // std::stringstream bufferedLines;
    // std::string line;


    // file.open("shaders/vertex.txt");
    // while(std::getline(file, line)) {
    //     std::cout << line << std::endl;
    // }

    if(!glfwInit()) {
        std::cout << "GLFW couldn't start" << std::endl;
        return -1;  
    }

    window = glfwCreateWindow(800, 500, "Game Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return -1;
    }

    glClearColor(0.5f, 0.24f, 0.5f, 1.0f);
     
    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}


// #include<bits/stdc++.h>
// using namespace std;


// int main(){

// return 0;
// }