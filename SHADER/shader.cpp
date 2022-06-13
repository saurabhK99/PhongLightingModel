#include "shader.h"

shader::shader() {
    shaderProgram = 0;
    uniformModel = 0; 
    uniformProjection = 0;
    uniformTexture = 0;
    uniformAmbientColor = 0;
    uniformAmbientIntensity = 0;
}

void shader::compileShader(const char* vs, const char* fs) {
    vShader = vs;
    fShader = fs;

    shaderProgram = glCreateProgram();

    addShader(vShader, GL_VERTEX_SHADER);
    addShader(fShader, GL_FRAGMENT_SHADER);

    //debugging
    GLchar log[1024];
    GLint result = 0;

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);

    if(!result) {
        glGetProgramInfoLog(shaderProgram, sizeof(log), NULL, log);
        std::cerr<<log<<std::endl;
    }

    glValidateProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &result);

    if(!result) {
        glGetProgramInfoLog(shaderProgram, sizeof(log), NULL, log);
        std::cerr<<log<<std::endl;
    }

    uniformModel = glGetUniformLocation(shaderProgram, "model");
    uniformView = glGetUniformLocation(shaderProgram, "view");
    uniformProjection = glGetUniformLocation(shaderProgram, "projection");

    uniformTexture = glGetUniformLocation(shaderProgram, "texUnit");

    uniformAmbientColor = glGetUniformLocation(shaderProgram, "dirLight.color");
    uniformAmbientIntensity = glGetUniformLocation(shaderProgram, "dirLight.ambientIntensity");

    uniformDirection = glGetUniformLocation(shaderProgram, "dirLight.direction");
    uniformDiffuseIntensity = glGetUniformLocation(shaderProgram, "dirLight.diffuseIntensity");

    uniformPosition = glGetUniformLocation(shaderProgram, "eyePos");

    uniformSpecularIntensity = glGetUniformLocation(shaderProgram, "material.specularIntensity");
    uniformShininess = glGetUniformLocation(shaderProgram, "material.shininess");
    
}

void shader::compileShaderFile(const char* vs, const char* fs) {
    std::ifstream vfin, ffin;
    vfin.open(vs, std::ios::in);

    if(!vfin) {
        std::cerr<<"No Vertex Shader Found!"<<std::endl;
        return;
    }

    ffin.open(fs, std::ios::in);

    if(!ffin) {
        std::cerr<<"No Fragment Shader Found!"<<std::endl;
        return;
    }
    
    std::string temp, vertexBuffer = "", fragmentBuffer = "";
    while(std::getline(vfin, temp)) {
        vertexBuffer.append(temp + "\n");
    }

    while(std::getline(ffin, temp)) {
        fragmentBuffer.append(temp + "\n");
    }

    compileShader(vertexBuffer.c_str(), fragmentBuffer.c_str());
}

GLint shader::getModelLocation() {
    //std::cout<<uniformModel<<std::endl;
    return uniformModel;
}

GLint shader::getViewLocation() {
    //std::cout<<uniformView<<std::endl;
    return uniformView;
}

GLint shader::getProjectionLocation() {
    //std::cout<<uniformProjection<<std::endl;
    return uniformProjection;
}

GLint shader::getTextureLocation() {
    //std::cout<<uniformTexture<<std::endl;
    return uniformTexture;
}

GLint shader::getAmbientColorLocation() {
    //std::cout<<uniformAmbientColor<<std::endl;
    return uniformAmbientColor;
}

GLint shader::getAmbientIntensityLocation() {
    //std::cout<<uniformAmbientIntensity<<std::endl;
    return uniformAmbientIntensity;
}

GLint shader::getDirectionLocation() {
    return uniformDirection;
}

GLint shader::getDiffuseIntensityLocation() {
    return uniformDiffuseIntensity;
}

GLint shader::getSpecularIntensityLocation() {
    return uniformSpecularIntensity;
}

GLint shader::getShininessLocation() {
    return uniformShininess;
}

GLint shader::getPositionLocation() {
    return uniformPosition;
}


void shader::useProgram() {
    glUseProgram(shaderProgram);
}

void shader::setProgram(GLuint val) {
    glUseProgram(val);
}

shader::~shader() {}