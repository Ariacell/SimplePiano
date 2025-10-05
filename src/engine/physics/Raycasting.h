#pragma once

#include <engine/core/log.h>
#include <engine/physics/Ray.h>
#include <fmt/core.h>
#include <io/glm_format.h>

#include <format>

namespace PianoPhysics {

bool CheckRayToAABBIntersection(Ray ray, const glm::vec3 &aabbMin,
                                const glm::vec3 &aabbMax, float &tHit) {
    PianoCore::Log::Info("Checking for intersect!");

    glm::vec3 invDir = 1.0f / ray.direction;
    glm::vec3 tMinVec = (aabbMin - ray.origin) * invDir;
    glm::vec3 tMaxVec = (aabbMax - ray.origin) * invDir;

    glm::vec3 t1 = glm::min(tMinVec, tMaxVec);
    glm::vec3 t2 = glm::max(tMinVec, tMaxVec);

    float tEnter = std::max(t1.x, std::max(t1.y, t1.z));
    float tExit = std::min(t2.x, std::min(t2.y, t2.z));

    if (tEnter > tExit || tExit < 0.0f) {
        PianoCore::Log::Info(fmt::format(
            "No intersection found for ray with origin {} and direction {}",
            ray.origin, ray.direction));

        return false;  // No intersection
    }

    tHit = tEnter;  // Store the closest intersection distance
    return true;    // Intersection found
}
}  // namespace PianoPhysics