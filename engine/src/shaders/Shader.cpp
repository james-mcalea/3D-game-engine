#include "Shader.h"

namespace fs = std::filesystem;

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // Load shader files
    fs::path exePath = fs::current_path();
    fs::path vPath = exePath / vertexPath;
    fs::path fPath = exePath / fragmentPath;


    std::ifstream vFile(vPath), fFile(fPath);
    if (!vFile.is_open() || !fFile.is_open()) {
        std::cerr << "ERROR: Failed to open shader files!" << std::endl;
        std::cerr << "Tried: " << vPath << " and " << fPath << std::endl;
        return;
    }

    std::stringstream vStream, fStream;
    vStream << vFile.rdbuf();
    fStream << fFile.rdbuf();

    std::string vertexCode = vStream.str();
    std::string fragmentCode = fStream.str();
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compile vertex shader
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    int success;
    char infoLog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "ERROR: Vertex shader compilation failed\n" << infoLog << std::endl;
    }

    // Compile fragment shader
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "ERROR: Fragment shader compilation failed\n" << infoLog << std::endl;
    }

    // Link shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "ERROR: Shader program linking failed\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
void Shader::Use() const {
    glUseProgram(ID);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& matrix) const {
    unsigned int loc = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}
