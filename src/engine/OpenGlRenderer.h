#pragma once
#include <engine/IRenderer.h>
#include <graphics/opengl/triangle.h>
#include <graphics/opengl/cube.h>
#include <graphics/shapes.h>
#include <glad/glad.h>
#include <iostream>

class OpenGlRenderer : public Engine::IRenderer
{
private:
    Shapes shapes;
    unsigned int rectangleVAO;
    unsigned int cubeVAO;
    Engine::IWindow* window = nullptr;

public:
    /// @brief Initialise the OpenGL window (must occur after window is created)
    /// @param window
    void Initialize(Engine::IWindow *window) override
    {
        this->window = window;
        using GLProcAddress = void* (*)(const char*);
        auto loader = reinterpret_cast<GLProcAddress>(window->GetWindowProcAddress());
        if (!gladLoadGLLoader(loader))
        {
            throw std::runtime_error("Failed to load OpenGl via Glad for window");
        }
        this->rectangleVAO = OpenGlGraphics::bindRectangle(shapes.getSampleRectangleData());
        this->cubeVAO = OpenGlGraphics::bindCube(shapes.getSampleCubeVerts());

        printf("Vendor graphic card: %s\n", glGetString(GL_VENDOR));
        printf("Renderer: %s\n", glGetString(GL_RENDERER));
        printf("Version GL: %s\n", glGetString(GL_VERSION));
        printf("Version GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

        std::cout << "OpenGL context initialized\n";
        glViewport(0, 0, 800, 600); // example values
    }

    void ClearScreen(float r, float g, float b, float a) override
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void DrawRectangle() override
    {
        glBindVertexArray(this->rectangleVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // Do more fun things here once I have time.
    }

    void DrawCube() override
    {
        glBindVertexArray(this->cubeVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // Do more fun things here once I have time.
    }

    void Present() override
    {
        if(!window) {
            throw std::runtime_error("Attempted to present OpenGL rendered scene without a handle to a running window!");
        }
        window->SwapBuffers();
    }
};
