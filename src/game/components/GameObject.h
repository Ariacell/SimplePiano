#pragma once

#include <memory>
#include <vector>

#include "Component.h"

namespace Component {
class GameObject {
public:
    ~GameObject();

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args);

    void Update(float deltaTime);
    void Render();

private:
    std::vector<std::unique_ptr<Component>> components;
};

}  // namespace Component