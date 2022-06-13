#include "texture.h"

texture::texture() {
    width = 0;
    height = 0;
    bitDepth = 0;
    textureID = 0;
}

void texture::loadTexture(const char* fileLocation) {
    unsigned char* textureData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);

    if(!textureData) {
        std::cout<<"Unable to read the texture file!!!";
        return;
    }

    glGenTextures(1, &textureID);

    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(textureData);

}

void texture::useTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}
    
texture::~texture() {
    glDeleteTextures(1, &textureID);
}