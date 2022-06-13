#include<iostream>
#include<GL/glew.h>

#include<GLFW/glfw3.h>

#ifndef WINDOW_INCLUDE
#define WINDOW_INCLUDE

class window {
    GLuint width, height;
    GLFWwindow* win;
    bool keys[1024] = {false};
    bool mouseFirstClicked = true;
    GLfloat lastX, lastY, xChange, yChange;

    static void handleKeys(GLFWwindow*, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow*, double xpos, double ypos);

    public:
        window();
        void createWindow(GLuint, GLuint, const char*);
        bool* getKeys();
        GLfloat getXChange();
        GLfloat getYChange();

        int windowShouldClose();
        void swapBuffers();
        ~window();
};

#endif