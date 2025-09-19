#pragma once

#include <string>

#include "Component.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"

namespace Component {

class ModelComponent : public Component {
public:
    ModelComponent(Ref<Model> model,
                   const std::shared_ptr<Shaders::IShader> &shader)
        : model(model), modelShader(shader){};

    void Draw(const std::shared_ptr<Shaders::IShader> &shader) {
        model.get()->Draw(modelShader);
    }

    Ref<Shaders::IShader> GetShader() {
        return modelShader;
    }

private:
    Ref<Model> model;
    Ref<Shaders::IShader> modelShader;
};
}  // namespace Component