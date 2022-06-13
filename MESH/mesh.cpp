#include "mesh.h"

mesh::mesh() {
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indexCount = 0;
}

void mesh::createMesh(GLfloat *vertices, GLsizei numVertices, unsigned int *indices, GLsizei numIndices) {
    indexCount = numIndices;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*numVertices, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*numIndices, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8 , 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8 , (void*)(sizeof(GLfloat)*3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8 , (void*)(sizeof(GLfloat)*5));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mesh::renderMesh() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

mesh::~mesh() {
    if(VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if(IBO != 0) {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }

    if(VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
    }
}