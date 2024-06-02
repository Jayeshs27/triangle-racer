#include "triangle_mesh.h"

TriangleMesh::TriangleMesh() {
    
    std::vector<float> positions = {
        -1.0f, -1.0f, 0.0f, 
         1.0f, -1.0f, 0.0f, 
        -1.0f,  1.0f, 0.0f, 
         1.0f,  1.0f, 0.0f

    };
    std::vector<int> colorIndices = {
        0, 1, 2, 3
    };
    std::vector<int> eleIndices = {
        0, 1, 2, 2, 3, 1
    };
    vertex_count = 6;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    VBOs.resize(2);
    glGenBuffers(2, VBOs.data());

    //position
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
    glEnableVertexAttribArray(0);

    //color indices
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, colorIndices.size() * sizeof(float), colorIndices.data(), GL_STATIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_INT, 4, (void*)0);
    glEnableVertexAttribArray(1);

    //element indices
    glGenBuffers(1, &EBOs);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, eleIndices.size() * sizeof(float), eleIndices.data(), GL_STATIC_DRAW);
    // glVertexAttribIPointer(1, 1, GL_INT, 4, (void*)0);
    // glEnableVertexAttribArray(1);


    // //color
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
    // glEnableVertexAttribArray(1);

}

void TriangleMesh::draw() { 
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBOs.data());
    glDeleteBuffers(1, &EBOs);
}