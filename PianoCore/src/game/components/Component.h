#pragma once

// Forward dec for GameObject to simplify the include structure

namespace Component {
class GameObject;

class Component {
public:
    virtual ~Component() = default;

    virtual void Update(float deltaTime) {
    }

    void SetParent(GameObject* parent) {
        this->parent = parent;
    }
    GameObject* GetParent() const {
        return parent;
    }

protected:
    GameObject* parent = nullptr;
};
}  // namespace Component