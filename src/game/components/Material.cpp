#include "Material.h"

std::shared_ptr<Shaders::IShader> Component::Material::GetShader() {
    return shader;
}