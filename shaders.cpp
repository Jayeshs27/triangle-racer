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
    glGetProgramiv(shader, GL_COMPILE_STATUS, &status);
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


    file.open("shaders/vertex.txt");
    while(std::getline(file, line)) {
        bufferedLines << line << std::endl;
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