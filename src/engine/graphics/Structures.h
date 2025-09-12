#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Renderer {
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};
struct Texture {
    unsigned int id;
    std::string type;
};
}  // namespace Renderer