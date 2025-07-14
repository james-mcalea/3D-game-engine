#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;
    float Speed;
    float Sensitivity;
    float Zoom;

    Camera(glm::vec3 startPosition);

    glm::mat4 GetViewMatrix() const;
    void ProcessKeyboard(char direction, float deltaTime);
    void ProcessMouse(float xoffset, float yoffset);

private:
    void updateVectors();
};
