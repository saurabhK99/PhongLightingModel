#include<iostream>
#include<GL/glew.h>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/string_cast.hpp>
#include<GLFW/glfw3.h>

#ifndef CAMERA_INCLUDE
#define CAMERA_INCLUDE

class camera {
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 worldUp;
    glm::vec3 up;
    glm::vec3 right;
    GLfloat yaw, pitch, movementSpeed, turnSpeed;
    void update();

    public:
        camera();
        camera(glm::vec3 positon, glm::vec3 worldUP, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat turnSpeed);
        void keyControl(bool* keys, GLfloat deltaTime);
        void mouseControl(GLfloat xChange, GLfloat yChange);
        glm::mat4 calculateViewMatrix();
        glm::vec3 getPosition();
        void reset(bool* keys);
        void display();
};

#endif