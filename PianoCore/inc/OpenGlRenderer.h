#pragma once
#define GLFW_INCLUDE_NONE
#include "IRenderer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/opengl/cube.h"
#include "graphics/opengl/triangle.h"
#include "graphics/shapes.h"
#include "shaders/IShader.h"
#include <glad/glad.h>
#include <stb_image/stb_image.h>

#include <filesystem>
#include <iostream>

class OpenGlRenderer : public Engine::IRenderer {
private:
    Shapes shapes;
    unsigned int rectangleVAO;
    unsigned int cubeVAO;

    unsigned int rectangleTexture;

    Engine::IWindow* window = nullptr;

public:
    /// @brief Initialise the OpenGL window (must occur after window is created)
    /// @param window
    void Initialize(Engine::IWindow& window) override;

    void ClearScreen(float r, float g, float b, float a) override;

    void SetWireframeRendering(bool shouldRenderWireframe) override;

    void DrawObject(const int& vertexArray,
                    const PianoCore::IndexBuffer& indexBuffer,
                    Shaders::IShader& shader) const override;

    void DrawObject(Component::GameObject* objectToDraw) const override;

    void DrawRectangle() override;

    void DrawCube() override;

    void LoadRectangleTexture();

    void Present() override;
};

void CheckOpenGlError(std::string callLocation);
