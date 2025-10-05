#pragma once
#include <glm/glm.hpp>

namespace PianoPhysics {
struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;
    float distance;

    Ray(glm::vec3 origin_, glm::vec3 direction_, float distance = 1.0F)
        : origin(origin_), direction(direction_) {
    }
};
}  // namespace PianoPhysics