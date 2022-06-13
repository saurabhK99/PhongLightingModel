#include<GL/glew.h>
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>

#ifndef LIGHT_INCLUDE
#define LIGHT_INCLUDE
 
class light {
    glm::vec3 color;
    glm::vec3 direction;
    GLfloat ambientIntensity, diffuseIntensity;


    public:
        light();
        light(glm::vec3 col, GLfloat ambIntensity, glm::vec3 dir, GLfloat diffIntensity);
        void useLight(GLint ambientColorLocation, GLint ambientIntensityLocation, GLint directionLocation, GLint diffuseIntensityLocation);
        void changeDiffuseIntensity(bool* keys);
        void changeAmbientIntensity(bool* keys);
        void changeColor(bool* keys);
        void changeDirection(bool* keys);
};

#endif