#include "light.h"

light::light() {
    color = glm::vec3(1.0, 1.0, 1.0);
    direction = glm::vec3(0.0, -1.0, 0.0);
    ambientIntensity = 0.5f;
    diffuseIntensity = 0.0f;
}

light::light(glm::vec3 col, GLfloat ambIntensity, glm::vec3 dir, GLfloat diffIntensity) {
    color = col;
    ambientIntensity = ambIntensity;
    
    direction = dir;
    diffuseIntensity = diffIntensity;


}

void light::changeDiffuseIntensity(bool* keys) {
    if(keys[GLFW_KEY_D] && keys[GLFW_KEY_KP_ADD]) {
        diffuseIntensity += 0.05;
        
        if(diffuseIntensity > 1.0) diffuseIntensity = 1;
    }

    else if(keys[GLFW_KEY_D] && keys[GLFW_KEY_KP_SUBTRACT]) {
        diffuseIntensity -= 0.05;
        
        if(diffuseIntensity < 0.0) diffuseIntensity = 0;
        
    }
}

void light::changeAmbientIntensity(bool* keys) {
    if(keys[GLFW_KEY_A] && keys[GLFW_KEY_KP_ADD]) {
        ambientIntensity += 0.05;
        
        if(ambientIntensity > 1.0) ambientIntensity = 1;
    }

    else if(keys[GLFW_KEY_A] && keys[GLFW_KEY_KP_SUBTRACT]) {
        ambientIntensity -= 0.05;
        
        if(ambientIntensity < 0.0) ambientIntensity = 0;
        
    }
}

void light::changeColor(bool* keys) {
    if(keys[GLFW_KEY_R] && keys[GLFW_KEY_KP_ADD]) {
        color.x += 0.05;
        
        if(color.x > 1.0) color.x = 1;
    }

    else if(keys[GLFW_KEY_R] && keys[GLFW_KEY_KP_SUBTRACT]) {
        color.x -= 0.05;
        
        if(color.x < 0.0) color.x = 0;
    }

    if(keys[GLFW_KEY_G] && keys[GLFW_KEY_KP_ADD]) {
        color.y += 0.05;
        
        if(color.y > 1.0) color.y = 1;
    }

    else if(keys[GLFW_KEY_G] && keys[GLFW_KEY_KP_SUBTRACT]) {
        color.y -= 0.05;
        
        if(color.y < 0.0) color.y = 0;
    }

    if(keys[GLFW_KEY_B] && keys[GLFW_KEY_KP_ADD]) {
        color.z += 0.05;
        
        if(color.z > 1.0) color.z = 1;
    }

    else if(keys[GLFW_KEY_B] && keys[GLFW_KEY_KP_SUBTRACT]) {
        color.z -= 0.05;
        
        if(color.z < 0.0) color.z = 0;
    }
}

void light::changeDirection(bool* keys) {
    if(keys[GLFW_KEY_X] && keys[GLFW_KEY_KP_ADD]) {
        direction.x += 0.05;
        
        if(direction.x > 2.0) direction.x = 2;
    }

    else if(keys[GLFW_KEY_X] && keys[GLFW_KEY_KP_SUBTRACT]) {
        direction.x -= 0.05;
        
        if(direction.x < -2.0) direction.x = -2;
    }

    if(keys[GLFW_KEY_Y] && keys[GLFW_KEY_KP_ADD]) {
        direction.y += 0.05;
        
        if(direction.y > 2.0) direction.y = 2;
    }

    else if(keys[GLFW_KEY_Y] && keys[GLFW_KEY_KP_SUBTRACT]) {
        direction.y -= 0.05;
        
        if(direction.y < -2.0) direction.y = -2;
    }

    if(keys[GLFW_KEY_Z] && keys[GLFW_KEY_KP_ADD]) {
        direction.z += 0.05;
        
        if(direction.z > 2.0) direction.z = 2;
    }

    else if(keys[GLFW_KEY_Z] && keys[GLFW_KEY_KP_SUBTRACT]) {
        direction.z -= 0.05;
        
        if(direction.z < -2.0) direction.z = -2.0;
    }
}

void light::useLight(GLint ambientColorLocation, GLint ambientIntensityLocation, GLint directionLocation, GLint diffuseIntensityLocation) {
    glUniform3f(ambientColorLocation, color.x, color.y, color.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);

    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

