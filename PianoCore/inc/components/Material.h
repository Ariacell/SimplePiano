#pragma once

#include "../shaders/IShader.h"

#include <memory>

#include "Component.h"

namespace Component {

class Material {
public:
    Material(std::shared_ptr<Shaders::IShader> shaderProgram,
             std::string texture_path)
        : shader(shaderProgram), texturePath(texture_path) {
    }

    std::shared_ptr<Shaders::IShader> GetShader();
    std::string GetTexturePath();

private:
    std::shared_ptr<Shaders::IShader> shader;
    std::string texturePath;
};
}  // namespace Component