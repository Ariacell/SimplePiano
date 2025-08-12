#pragma once
#include <engine/IRenderer.h>
#include <engine/graphics/IndexBuffer.h>
#include <engine/graphics/opengl/cube.h>
#include <engine/graphics/opengl/triangle.h>
#include <engine/graphics/shapes.h>
#include <engine/shaders/IShader.h>
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
    void Initialize(Engine::IWindow* window) override;

    void ClearScreen(float r, float g, float b, float a) override;

    void DrawObject(const int& vertexArray,
                    const Renderer::IndexBuffer& indexBuffer,
                    const Shaders::IShader& shader) const override;

    void DrawRectangle() override;

    void DrawCube() override;

    void LoadRectangleTexture();

    void Present() override;
};
