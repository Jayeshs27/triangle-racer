#if !defined(__TRIANGLE_MESH_H__)
#define __TRIANGLE_MESH_H__

#include "headers.h"
#include "libraries.h"

class TriangleMesh {
public:
TriangleMesh();
void draw();
~TriangleMesh();

private:
unsigned int EBOs, VAO, vertex_count;
std::vector<unsigned int> VBOs;
};

#endif // __TRIANGLE_MESH_H__
