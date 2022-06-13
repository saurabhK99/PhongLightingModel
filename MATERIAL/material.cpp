#include "material.h"


material::material() {
    shininess = 0;
    specularIntensity = 0;
}

material::material(GLfloat shine, GLfloat specIntensity) {
    shininess = shine;
    specularIntensity = specIntensity;
}

void material::changeSpecularIntensity(bool* keys) {
    if(keys[GLFW_KEY_S] && keys[GLFW_KEY_KP_ADD]) {
        specularIntensity += 0.05;
        
        if(specularIntensity > 1.0) specularIntensity = 1;
    }

    else if(keys[GLFW_KEY_S] && keys[GLFW_KEY_KP_SUBTRACT]) {
        specularIntensity -= 0.05;
        
        if(specularIntensity < 0.0) specularIntensity = 0;
        
    }
}

void material::useMaterial(GLuint shininessLoc, GLuint specularIntensityLoc) {
    glUniform1f(shininessLoc, shininess);
    glUniform1f(specularIntensityLoc, specularIntensity);
}