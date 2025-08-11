#pragma once
#include <engine/IWindow.h>
#include <engine/shaders/IShader.h>

namespace Engine {

class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual void Initialize(Engine::IWindow* window) = 0;
    virtual void ClearScreen(float r, float g, float b, float a) = 0;
    virtual void DrawObject(const int& vertexArray, const int& indexBuffer,
                            const Shaders::IShader& shader) const = 0;
    virtual void DrawRectangle() = 0;
    virtual void DrawCube() = 0;
    virtual void Present() = 0;
};
}  // namespace Engine