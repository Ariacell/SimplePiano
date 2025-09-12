#pragma once

#include <string>

#include "Component.h"
#include "Material.h"
#include "Mesh.h"

namespace Component {

class ModelComponent : public Component {
public:
    ModelComponent(std::shared_ptr<Mesh1> mesh, std::shared_ptr<Material> mat)
        : mesh(mesh), mat(mat){};

    Mesh1* GetMesh() const {
        return mesh.get();
    }
    Material* GetTexture() const {
        return mat.get();
    }

private:
    std::shared_ptr<Mesh1> mesh;
    std::shared_ptr<Material> mat;
};
}  // namespace Component