#include<iostream>
#include<cstring>
#include<fstream>
#include<GL/glew.h>

#ifndef SHADER_INCLUDE
#define SHADER_INCLUDE

class shader {
    const char* vShader;
    const char* fShader;
    GLuint shaderProgram;
    GLint  uniformModel, uniformProjection, uniformView, uniformTexture, uniformPosition;
    GLint uniformAmbientColor, uniformAmbientIntensity;
    GLint uniformDirection, uniformDiffuseIntensity;
    GLint uniformSpecularIntensity, uniformShininess;

    void addShader(const char* sCode, GLenum type) {
        GLuint newShader = glCreateShader(type);

        const char* code[1];
        code[0] = sCode;

        GLint len[1];
        len[0] = strlen(sCode);

        glShaderSource(newShader, 1, code, len);
        glCompileShader(newShader);

        //debugging
        GLchar log[1024];
        GLint res = 0;

        glGetShaderiv(newShader, GL_COMPILE_STATUS, &res);

        if(!res) {
            glGetShaderInfoLog(newShader, sizeof(log), NULL, log);
            std::cerr<<log<<std::endl;
        }

        glAttachShader(shaderProgram, newShader);
    }

    public:
        shader();
        void compileShader(const char*, const char*);
        void compileShaderFile(const char*, const char*);

        GLint getModelLocation();
        GLint getViewLocation();
        GLint getProjectionLocation();
        GLint getTextureLocation();
        GLint getAmbientColorLocation();
        GLint getAmbientIntensityLocation();
        GLint getDirectionLocation();
        GLint getDiffuseIntensityLocation();
        GLint getSpecularIntensityLocation();
        GLint getShininessLocation();
        GLint getPositionLocation();
        
        void useProgram();
        void setProgram(GLuint);
        ~shader();
};

#endif