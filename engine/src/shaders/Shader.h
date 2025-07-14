#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp> // for glm::value_ptr


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void Use() const;
    void SetMat4(const std::string& name, const glm::mat4& matrix) const;

};
