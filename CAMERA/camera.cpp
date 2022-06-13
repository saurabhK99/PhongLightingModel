#include "camera.h"

camera::camera() {
    position = glm::vec3(0.0, 0.0, 0.0);
    worldUp = glm::vec3(0.0, 1.0, 0.0);;
    yaw = 0.0;
    pitch = 0.0;
    movementSpeed = 3.0;
    turnSpeed = 1.0;

    front = glm::vec3(0.0, 0.0, -1.0);

    update();
}

camera::camera(glm::vec3 thePosition, glm::vec3 theWorldUP, GLfloat theYaw, GLfloat thePitch, GLfloat theMovementSpeed, GLfloat theTurnSpeed) {
    position = thePosition;
    worldUp = theWorldUP;
    yaw = theYaw;
    pitch = thePitch;
    movementSpeed = theMovementSpeed;
    turnSpeed = theTurnSpeed;

    front = glm::vec3(0.0, 0.0, -1.0);

    update();
}

void camera::update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z =  sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void camera::keyControl(bool* keys, GLfloat deltaTime) {
    GLfloat velocity = deltaTime * movementSpeed;

    if(keys[GLFW_KEY_UP]) {
        position.x = position.x + (front.x * velocity);
        position.z = position.z + (front.z * velocity);
    }

    if(keys[GLFW_KEY_DOWN]) {
        position.x = position.x - (front.x * velocity);
        position.z = position.z - (front.z * velocity);
    }

    if(keys[GLFW_KEY_LEFT]) {
        position.x = position.x - (right.x * velocity);
        position.z = position.z - (right.z * velocity);
    }

    if(keys[GLFW_KEY_RIGHT]) {
        position.x = position.x + (right.x * velocity);
        position.z = position.z + (right.z * velocity);
    }
}

void camera::reset(bool* keys) {
    if(keys[GLFW_KEY_R]) {
        position = glm::vec3(0.0f,1.0f,-2.5f);
        yaw = 90.0f;
        pitch = 0.0f;
    }
}

void camera::mouseControl(GLfloat xChange, GLfloat yChange) {
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch += yChange;

    if(pitch > 89.0f) {
        pitch = 89.0f;
    }

    if(pitch < -89.0f) {
        pitch = -89.0f;
    }

    update();
    
}

glm::mat4 camera::calculateViewMatrix() {
    return glm::lookAt(position, front+position, up);
}

glm::vec3  camera::getPosition() {
    return position;
}

void camera::display() {
    std::cout<<"Position : "<<glm::to_string(position)<<std::endl;
    std::cout<<"World Up : "<<glm::to_string(worldUp)<<std::endl;
    std::cout<<"Cam Up   : "<<glm::to_string(up)<<std::endl;
    std::cout<<"Right    : "<<glm::to_string(right)<<std::endl;

    glm::vec3 total = worldUp+up;
    std::cout<<"Total    : "<<glm::to_string(total)<<std::endl;

}