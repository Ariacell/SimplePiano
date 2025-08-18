#pragma once

#include <string>

#include "Component.h"
#include "Material.h"
#include "Mesh.h"

namespace Component {

class ModelComponent : public Component {
public:
    ModelComponent(Mesh mesh, Material mat) : mesh(mesh), mat(mat){};

    const Mesh GetMesh() const {
        return mesh;
    }
    const Material GetTexture() const {
        return mat;
    }

private:
    Mesh mesh;
    Material mat;
};
}  // namespace Component