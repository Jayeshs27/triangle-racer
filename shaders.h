#include "headers.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

unsigned int make_module(const std::string& filepath, unsigned int module_type);
unsigned int make_shaders(const std::string& vertex_filepath, const std::string& fragment_filepath);