#include "Engine.h"
#include "../renderer/Renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

GLFWwindow* window = nullptr;
float lastX = 640, lastY = 360;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Engine::Engine(int width, int height, const char* title)
    : m_Width(width), m_Height(height), m_Title(title), m_Running(true),
      m_Camera(glm::vec3(0.0f, 0.0f, 3.0f)) {}

Engine::~Engine() {
    Shutdown();
}

void Engine::Init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        m_Running = false;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        m_Running = false;
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    // After glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window, this);

    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xpos, double ypos) {
        Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(win));
        if (!engine) return;

        static float lastX = 640.0f;
        static float lastY = 360.0f;
        static bool firstMouse = true;

        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
            return; // ⛔ avoid applying deltas on first frame
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;  // inverted Y axis

        lastX = xpos;
        lastY = ypos;

        engine->m_Camera.ProcessMouse(xoffset, yoffset);
    });


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    m_Renderer = std::make_unique<Renderer>();
    m_Renderer->Init();
}

void Engine::Run() {
    Init();
    if (!m_Running) return;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        Update();
        Render();
        glfwSwapBuffers(window);
    }
}

void Engine::Update() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) m_Camera.ProcessKeyboard('W', deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) m_Camera.ProcessKeyboard('S', deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) m_Camera.ProcessKeyboard('A', deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) m_Camera.ProcessKeyboard('D', deltaTime);
    //  std::cout << "Camera Position: "
    //       << m_Camera.Position.x << ", "
    //       << m_Camera.Position.y << ", "
    //       << m_Camera.Position.z << std::endl;

}

void Engine::Render() {
    
    glm::mat4 view = m_Camera.GetViewMatrix();
glm::mat4 projection = glm::perspective(
    glm::radians(m_Camera.Zoom),
    static_cast<float>(m_Width) / m_Height,
    0.01f, 100.0f);  // make sure near is small (not 1.0f)
    m_Renderer->Render(view, projection);
    
}

void Engine::Shutdown() {
    m_Renderer.reset();
    glfwDestroyWindow(window);
    glfwTerminate();
}