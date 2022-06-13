#include<iostream>
#include<GL/glew.h>

#include "stb_image.h"

#ifndef TEXTURE_INCLUDE
#define TEXTURE_INCLUDE

class texture {
    GLuint textureID;
    int width, height, bitDepth;

    public:
        texture();
        void loadTexture(const char* fileLocation);
        void useTexture();
        ~texture();
};

#endif