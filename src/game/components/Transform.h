#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Component {

struct Transform {
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    Transform()
        : position(0.0f), rotation(1.0f, 0.0f, 0.0f, 0.0f), scale(1.0f) {
    }

    void translate(const glm::vec3& translation) {
        position += translation;
    }

    void rotate(const glm::quat& deltaRotation) {
        rotation = deltaRotation * rotation;
    }

    void scaleBy(const glm::vec3& factor) {
        scale *= factor;
    }

    glm::mat4 getWorldMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model *= glm::mat4_cast(rotation);
        model = glm::scale(model, scale);
        return model;
    }
};
}  // namespace Component
