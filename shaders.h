#if !defined(__SHADERS_H__)
#define __SHADERS_H__

#include "libraries.h"

unsigned int make_module(const std::string& filepath, unsigned int module_type);
unsigned int make_shaders(const std::string& vertex_filepath, const std::string& fragment_filepath);

#endif // __SHADERS_H__
