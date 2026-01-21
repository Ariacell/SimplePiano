#include "components/GameObject.h"

#include "components/ModelComponent.h"

namespace Component {

GameObject::~GameObject() {
    components.clear();  // Unique_ptr handles deletion
}

void GameObject::Update(float deltaTime) {
    for (auto& comp : components) {
        comp->Update(deltaTime);
    }
}

}  // namespace Component