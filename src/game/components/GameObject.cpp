#include "GameObject.h"

Component::GameObject::~GameObject() {
    components.clear();  // Unique_ptr handles deletion
}

void Component::GameObject::Update(float deltaTime) {
    for (auto& comp : components) {
        comp->Update(deltaTime);
    }
}

template <typename T, typename... Args>
T* Component::GameObject::AddComponent(Args&&... args) {
    static_assert(
        std::is_base_of<Component, T>::value,
        "Attempted to add a non-Component type object to a Gameobject");

    T* comp = new T(std::forward<Args>(args)...);
    comp->SetOwner(this);
    components.emplace_back(comp);
    return comp;
}
