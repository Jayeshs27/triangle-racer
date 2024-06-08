#include "shaders.h"

unsigned int make_shaders(const std::string& vertex_filepath, const std::string& fragment_filepath) {
    unsigned int shader, vertex_shader_module, fragment_shader_module;
    shader = glCreateProgram();
    vertex_shader_module = make_module(vertex_filepath, GL_VERTEX_SHADER);
    fragment_shader_module = make_module(fragment_filepath, GL_FRAGMENT_SHADER);

    glAttachShader(shader, vertex_shader_module);
    glAttachShader(shader, fragment_shader_module);

    glLinkProgram(shader);

    int status;
    glGetProgramiv(shader, GL_LINK_STATUS, &status);
    if(!status){
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errorLog);
        std::cout << "Shader Module Linking error:\n" << errorLog << std::endl;
    }

    glDeleteShader(vertex_shader_module);
    glDeleteShader(fragment_shader_module);

    return shader;
}

unsigned int make_module(const std::string& filepath, unsigned int module_type) {
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;


    file.open(filepath);
    while(std::getline(file, line)) {
        bufferedLines << line << '\n';
    }
    std::string shaderSourceStr = bufferedLines.str();
    const char* shaderSrc = shaderSourceStr.c_str();
    bufferedLines.str("");
    file.close();

    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    int status;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &status);
    if(!status){
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        std::cout << "Shader Module compilation error:\n" << errorLog << std::endl;
    }
    return shaderModule;
}

void update_shader(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 camera_pos,
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