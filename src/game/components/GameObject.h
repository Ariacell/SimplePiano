#pragma once

#include <memory>
#include <vector>

#include "Component.h"

namespace Component {
class GameObject {
public:
    ~GameObject();

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        static_assert(
            std::is_base_of<Component, T>::value,
            "Attempted to Add a non-Component type object on a Gameobject");

        T* comp = new T(std::forward<Args>(args)...);
        comp->SetParent(this);
        components.emplace_back(comp);
        return comp;
    }

    template <typename T>
    T* GetComponent() {
        static_assert(
            std::is_base_of<Component, T>::value,
            "Attempted to Get a non-Component type object on a Gameobject");

        for (const auto& c : components) {
            if (auto* target = dynamic_cast<T*>(c.get())) {
                return target;
            }
        }

        return nullptr;  // Not found
    }

    void Update(float deltaTime);
    void Render();

private:
    std::vector<std::unique_ptr<Component>> components;
};

}  // namespace Component