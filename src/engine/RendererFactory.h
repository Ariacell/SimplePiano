#pragma once
#include <engine/IRenderer.h>
#include <engine/OpenGlRenderer.h>

#include <memory>
#include <string>

enum class RendererType { OpenGL, DirectX };

class RendererFactory {
public:
    static std::unique_ptr<Engine::IRenderer> CreateRenderer(
        RendererType type) {
        switch (type) {
            case RendererType::OpenGL:
                return std::make_unique<OpenGlRenderer>();
            case RendererType::DirectX:
                std::cout << "DirectX not yet implemented" << std::endl;
                return nullptr;
            default:
                return nullptr;
        }
    }
};
