#include "components/BoundingBoxComponent.h"

#include "graphics/OpenGLLine.h"

Component::BoundingBoxComponent::BoundingBoxComponent(Model& model) {
    glm::vec3 minBounds = glm::vec3(0.0f);
    glm::vec3 maxBounds = glm::vec3(0.0f);
    for (auto mesh : model.meshes) {
        for (auto vert : mesh.vertices) {
            if (vert.Position.x < minBounds.x)
                minBounds.x = vert.Position.x;
            if (vert.Position.y < minBounds.y)
                minBounds.y = vert.Position.y;
            if (vert.Position.z < minBounds.z)
                minBounds.z = vert.Position.z;
            if (vert.Position.x > maxBounds.x)
                maxBounds.x = vert.Position.x;
            if (vert.Position.y > maxBounds.y)
                maxBounds.y = vert.Position.y;
            if (vert.Position.z > maxBounds.z)
                maxBounds.z = vert.Position.z;
        }
    }
    this->minBounds = minBounds;
    this->maxBounds = maxBounds;
}

Component::BoundingBoxComponent::BoundingBoxComponent(
    glm::vec3 heightWidthDepth)
    : minBounds(glm::vec3(0.0F)), maxBounds(heightWidthDepth) {
}

glm::vec3 Component::BoundingBoxComponent::GetMinExtents() {
    return minBounds;
}

glm::vec3 Component::BoundingBoxComponent::GetMaxExtents() {
    return maxBounds;
}

void Component::BoundingBoxComponent::DrawDebug(glm::mat4 proj,
                                                glm::mat4 view) {
    std::vector<Ptr<Line>> lines;
    lines.reserve(12);

    lines.emplace_back(std::make_unique<Line>(
        glm::vec3(minBounds.x, minBounds.y, minBounds.z),
        glm::vec3(maxBounds.x, minBounds.y, minBounds.z)));
    lines.emplace_back(std::make_unique<Line>(
        glm::vec3(minBounds.x, minBounds.y, minBounds.z),
        glm::vec3(minBounds.x, maxBounds.y, minBounds.z)));
    lines.emplace_back(std::make_unique<Line>(
        glm::vec3(minBounds.x, minBounds.y, minBounds.z),
        glm::vec3(minBounds.x, minBounds.y, maxBounds.z)));

    lines.emplace_back(std::make_unique<Line>(
        glm::vec3(minBounds.x, maxBounds.y, maxBounds.z),
        glm::vec3(maxBounds.x, maxBounds.y, maxBounds.z)));
    lines.emplace_back(std::make_unique<Line>(
        glm::vec3(maxBounds.x, minBounds.y, maxBounds.z),
        glm::vec3(maxBounds.x, maxBounds.y, maxBounds.z)));
    lines.emplace_back(std::make_unique<Line>(
        glm::vec3(maxBounds.x, maxBounds.y, minBounds.z),
        glm::vec3(maxBounds.x, maxBounds.y, maxBounds.z)));

    lines.emplace_back(std::make_unique<Line>(
        glm::vec3(minBounds.x, maxBounds.y, minBounds.z),
        glm::vec3(minBounds.x, maxBounds.y, maxBounds.z)));
    lines.emplace_back(std::make_unique<Line>(
        glm::vec3(minBounds.x, maxBounds.y, minBounds.z),
        glm::vec3(maxBounds.x, maxBounds.y, minBounds.z)));

    lines.emplace_back(std::make_unique<Line>(
        glm::vec3(maxBounds.x, minBounds.y, minBounds.z),
        glm::vec3(maxBounds.x, maxBounds.y, minBounds.z)));
    lines.emplace_back(std::make_unique<Line>(
        glm::vec3(maxBounds.x, minBounds.y, minBounds.z),
        glm::vec3(maxBounds.x, minBounds.y, maxBounds.z)));

    lines.emplace_back(std::make_unique<Line>(
        glm::vec3(minBounds.x, minBounds.y, maxBounds.z),
        glm::vec3(maxBounds.x, minBounds.y, maxBounds.z)));
    lines.emplace_back(std::make_unique<Line>(
        glm::vec3(maxBounds.x, minBounds.y, maxBounds.z),
        glm::vec3(maxBounds.x, maxBounds.y, maxBounds.z)));

    for (auto& line : lines) {
        line->setMVP(proj * view);
        line->draw();
    }
}
