#if !defined(__TRIANGLE_MESH_H__)
#define __TRIANGLE_MESH_H__

#include "libraries.h"

class TriangleMesh {
public:
glm::vec3 translateVec;
TriangleMesh(std::vector<float> positions, int color);
void draw();
void TranslatePos(glm::vec3 pos);
~TriangleMesh();

private:
unsigned int EBOs, VAO, vertex_count;
std::vector<unsigned int> VBOs;
};

#endif // __TRIANGLE_MESH_H__
