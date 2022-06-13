#include "window.h"

window::window() {
    width = 0;
    height = 0;

    if(!glfwInit()) {
        std::cerr<<"GLFW initialization failed!"<<std::endl;
    }
    
}

void window::createWindow(GLuint w, GLuint h, const char* name) {

    //setting the hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    win = glfwCreateWindow(w,h,name,0,0);
    width = w;
    height = h;

    if(!win) {
        std::cerr<<"Window creation failed!"<<std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(win);

    glfwSetKeyCallback(win, handleKeys);
    glfwSetCursorPosCallback(win, handleMouse);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cerr<<"GLEW initialization failed!"<<std::endl;
        glfwDestroyWindow(win);
        glfwTerminate();
        return;
    }

    GLint bw, bh;

    glfwGetFramebufferSize(win, &bw, &bh);

    glViewport(0,0,bw,bh);

    glfwSetWindowUserPointer(win, this);
}

int window::windowShouldClose() {
    return glfwWindowShouldClose(win);
}

void window::handleMouse(GLFWwindow* w, double xpos, double ypos) {
    window* theWin = static_cast<window*>(glfwGetWindowUserPointer(w));

    if(theWin->mouseFirstClicked) {
        theWin->lastX = xpos;
        theWin->lastY = ypos;

        theWin->mouseFirstClicked = false;
    }

    theWin->xChange = xpos - theWin->lastX;
    theWin->yChange = theWin->lastY - ypos;

    theWin->lastX = xpos;
    theWin->lastY = ypos;
 }

 bool* window::getKeys() {
     return keys;
 }

GLfloat window::getYChange() {
    GLfloat change = yChange;
    yChange = 0.0f;
    return change;
 }

 GLfloat window::getXChange() {
     GLfloat change = xChange;
     xChange = 0.0f;
     return change;
 }

void window::handleKeys(GLFWwindow* w, int key, int code, int action, int mode) {
    window* theWin = static_cast<window*>(glfwGetWindowUserPointer(w));

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(w, GL_TRUE);
    }

    if(key>0 && key<1024) {
        if(action == GLFW_PRESS) {
            std::cout<<"Pressed : "<<key<<std::endl;
            theWin->keys[key] = true;
        }

        if(action == GLFW_RELEASE) {
            std::cout<<"Released : "<<key<<std::endl;
            theWin->keys[key] = false;
        }
    }
 }

void window::swapBuffers() {
    glfwSwapBuffers(win);
}


window::~window() {
    glfwDestroyWindow(win);
    glfwTerminate();
}