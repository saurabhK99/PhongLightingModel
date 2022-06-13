#include<GL/glew.h>

#ifndef MESH_INCLUDE
#define MESH_INCLUDE
class mesh {
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
    public:
        mesh();
        void createMesh(GLfloat*,GLsizei, unsigned int*, GLsizei);
        void renderMesh();
        ~mesh();
};
#endif