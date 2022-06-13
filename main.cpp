#define STB_IMAGE_IMPLEMENTATION

#include<iostream>
#include<cstring>
#include<vector>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

//maths library
#include<glm/gtx/string_cast.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "MESH/mesh.h"
#include "SHADER/shader.h"
#include "WIN/window.h"
#include "CAMERA/camera.h"
#include "TEXTURE/texture.h"
#include "LIGHT/light.h"
#include "MATERIAL/material.h"


void calculateAverageNormal(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset) {
    for (size_t i = 0; i < indiceCount; i += 3) {
        unsigned int in0 = indices[i] * vLength;
        unsigned int in1 = indices[i + 1] * vLength;
        unsigned int in2 = indices[i + 2] * vLength;

        glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
        glm::vec3 normal = glm::cross(v1, v2);

        normal = glm::normalize(normal);

        in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;

        vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
        vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
        vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
    }

    for (size_t i = 0; i < verticeCount / vLength; i++) {
        unsigned int nOffset = i * vLength + normalOffset;

        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);

        vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
    }
}


GLfloat vertices[] = {
    -1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, -1.0, 1.0, 0.5, 0.0, 0.0, 0.0, 0.0,
    1.0, -1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.5, 0.5, 1.0, 0.0, 0.0, 0.0
};

unsigned int indices[] = {
    0,3,1,
    1,3,2,
    2,3,0,
    0,1,2
};

GLfloat groundVertices[] = {
    -10.0, 0.0, 10.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    10.0, 0.0, 10.0, 1.0, 1.0, 0.0, 0.0, 0.0,
    10.0, 0.0, -10.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    -10.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 0.0
};

unsigned int groundIndices[] = {
    0, 1, 2,
    2, 3, 0
};


int main() {
    std::vector<mesh*> meshList;
    calculateAverageNormal(indices, 12, vertices, 32, 8, 5);
    calculateAverageNormal(groundIndices, 6, groundVertices, 32, 8, 5);

    window w;
    mesh *m1;
    mesh *m2;
    shader s;
    camera c(glm::vec3(0.0f,1.0f,-2.5f),glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 4.0f, 0.75f);
    texture t;
    texture groundT;
    light l(glm::vec3(1.0, 1.0, 1.0), 0.3, glm::vec3(2.0, -1.0, -2.0), 1.0);
    material mat(32.0, 1.0);

    GLint uniformModel=0, uniformProjection=0, uniformView = 0;
    GLint uniformTexture = 0;
    GLint uniformAmbientColor = 0, uniformAmbientIntensity = 0;
    GLint uniformDiffuseIntensity = 0, uniformDirection = 0;
    GLint uniformShininess = 0, uniformSpecularIntensity = 0;

    GLfloat deltaTime = 0.0f, lastTime = 0.0f;

    glm::mat4 projection(1.0f);
    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 identity(1.0f);
    

    w.createWindow(1920, 1080, "TESTING");
    
    m1 = new mesh();
    m2 = new mesh();

    meshList.push_back(m1);
    meshList.push_back(m2);
    meshList[0]->createMesh(vertices, 32,indices, 12);
    meshList[1]->createMesh(groundVertices, 32,groundIndices, 6);
        

    t.loadTexture("TEXTURE/brick.png");
    groundT.loadTexture("TEXTURE/ground.png");

    s.compileShaderFile("SHADER/shader.vert", "SHADER/shader.frag");

    glEnable(GL_DEPTH_BUFFER);

    projection = glm::perspective(45.0f, (GLfloat)(800/600) ,0.1f, 100.0f);
    //std::cout<<glm::to_string(projection)<<std::endl;

    while(!w.windowShouldClose()) { 

        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        glfwPollEvents();

        c.keyControl(w.getKeys(), deltaTime);
        c.mouseControl(w.getXChange(), w.getYChange());
        //c.display();

        glClearColor(1.0, 1.0, 1.0 ,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        s.useProgram();
    
        //std::cout<<glm::to_string(model)<<std::endl;
        
        uniformModel = s.getModelLocation();
        uniformView = s.getViewLocation();
        uniformProjection = s.getProjectionLocation();
        uniformTexture = s.getTextureLocation();
        uniformAmbientColor = s.getAmbientColorLocation();
        uniformAmbientIntensity = s.getAmbientIntensityLocation();
        uniformDirection = s.getDirectionLocation();
        uniformDiffuseIntensity = s.getDiffuseIntensityLocation();
        uniformShininess = s.getShininessLocation();
        uniformSpecularIntensity = s.getSpecularIntensityLocation();

        //model = glm::rotate(model, 10.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        //std::cout<<"\nRotation : "<<glm::to_string(model)<<std::endl;
        
        view = c.calculateViewMatrix();

        model = glm::translate(model, glm::vec3(0.0, 1.6, 0));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

        mat.changeSpecularIntensity(w.getKeys());
        l.changeAmbientIntensity(w.getKeys());
        l.changeDiffuseIntensity(w.getKeys());
        l.changeColor(w.getKeys());
        l.changeDirection(w.getKeys());

        l.useLight(uniformAmbientColor, uniformAmbientIntensity, uniformDirection, uniformDiffuseIntensity);

        mat.useMaterial(uniformShininess, uniformSpecularIntensity);

        glUniform1i(uniformTexture, 0);
        t.useTexture();

        meshList[0]->renderMesh();

        model = identity;
        //model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        groundT.useTexture();
        meshList[1]->renderMesh();

        c.reset(w.getKeys());

        w.swapBuffers();

        s.setProgram(0);
    }

    return 0;
}