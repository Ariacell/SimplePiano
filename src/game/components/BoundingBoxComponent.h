#pragma once
#include <game/components/Model.h>

#include "Component.h"

namespace Component {

class BoundingBoxComponent : public Component {
public:
    BoundingBoxComponent(Model &model);
    BoundingBoxComponent(glm::vec3 heightWidthDepth);
    glm::vec3 GetMinExtents();
    glm::vec3 GetMaxExtents();

private:
    glm::vec3 minBounds;
    glm::vec3 maxBounds;
};
}  // namespace Component