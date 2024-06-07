#if !defined(__MATERIAL_H__)
#define __MATERIAL_H__

#include "libraries.h"

class Material
{
public:
  Material(const char *filename);
  ~Material();
  void use();

private:
  unsigned int texture;
};

#endif // __MATERIAL_H__
