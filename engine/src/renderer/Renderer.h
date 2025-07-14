#pragma once
#include "../shaders/Shader.h"

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <filesystem>

class Renderer {
public:
    Renderer();
    ~Renderer();

    void Init();
    void Render(const glm::mat4& view, const glm::mat4& projection);
};
