#include<GL/glew.h>
#include<GLFW/glfw3.h>

#ifndef MATERIAL_INCLUDE
#define MATERIAL_INCLUDE

class material {
    GLfloat specularIntensity, shininess;
    public:
        material();
        material(GLfloat shine, GLfloat specIntensity);
        void changeSpecularIntensity(bool* keys);
        void useMaterial(GLuint shininessLoc, GLuint specularIntensityLoc);
};

#endif