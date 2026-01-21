#pragma once
#include "IWindow.h"
#include "graphics/IndexBuffer.h"
#include "shaders/IShader.h"
#include "components/GameObject.h"

namespace Engine {

class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual void Initialize(Engine::IWindow& window) = 0;
    virtual void ClearScreen(float r, float g, float b, float a) = 0;

    virtual void SetWireframeRendering(bool shouldRenderWireframe) = 0;

    virtual void DrawObject(const int& vertexArray,
                            const PianoCore::IndexBuffer& indexBuffer,
                            Shaders::IShader& shader) const = 0;

    virtual void DrawObject(Component::GameObject* objectToDraw) const = 0;
    virtual void DrawRectangle() = 0;
    virtual void DrawCube() = 0;
    virtual void Present() = 0;

protected:
    bool isWireframeRenderingEnabled = false;
};
}  // namespace Engine