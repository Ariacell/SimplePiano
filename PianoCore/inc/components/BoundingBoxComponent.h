#pragma once
#include "Model.h"

#include "Component.h"

namespace Component {

class BoundingBoxComponent : public Component {
public:
    BoundingBoxComponent(Model &model);
    BoundingBoxComponent(glm::vec3 heightWidthDepth);
    glm::vec3 GetMinExtents();
    glm::vec3 GetMaxExtents();

    void DrawDebug(glm::mat4 proj, glm::mat4 view);

private:
    glm::vec3 minBounds;
    glm::vec3 maxBounds;
};
}  // namespace Component