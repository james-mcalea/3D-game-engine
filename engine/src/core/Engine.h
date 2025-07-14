#pragma once
#include <memory>
#include <iostream>

#include "../camera/Camera.h"
#include "../renderer/Renderer.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
class Renderer;

class Engine {
    public:
        Engine(int width, int height, const char* title);
        ~Engine();

        void Run();
    
    private:
        void Init();
        void Update();
        void Render();
        void Shutdown();

        int m_Width;
        int m_Height;
        const char* m_Title;

        bool m_Running;

    std::unique_ptr<Renderer> m_Renderer;
    Camera m_Camera;

};