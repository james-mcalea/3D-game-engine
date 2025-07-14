#include "Camera.h"

Camera::Camera(glm::vec3 startPosition)
    : Position(startPosition), WorldUp(0.0f, 1.0f, 0.0f),
      Yaw(-90.0f), Pitch(0.0f),
      Speed(2.5f), Sensitivity(0.001f), Zoom(45.0f)
{
    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    updateVectors();
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
}


void Camera::ProcessKeyboard(char direction, float deltaTime) {
    float velocity = Speed * deltaTime;
    if (direction == 'W') Position += Front * velocity;
    if (direction == 'S') Position -= Front * velocity;
    if (direction == 'A') Position -= Right * velocity;
    if (direction == 'D') Position += Right * velocity;
}

void Camera::ProcessMouse(float xoffset, float yoffset) {
    xoffset *= Sensitivity;  // typically 0.1f
    yoffset *= Sensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;

    updateVectors();  // update Front/Up/Right vectors
}


void Camera::updateVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}
