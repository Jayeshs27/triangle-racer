#if !defined(__SHADERS_H__)
#define __SHADERS_H__

#include "libraries.h"

unsigned int make_module(const std::string& filepath, unsigned int module_type);
unsigned int make_shaders(const std::string& vertex_filepath, const std::string& fragment_filepath);
void update_shader(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 camera_pos,
                  glm::vec3 camera_target, glm::vec3 up, unsigned int &shader);
#endif // __SHADERS_H__
