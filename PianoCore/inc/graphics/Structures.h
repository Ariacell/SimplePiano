#pragma once

#include <glm/glm.hpp>
#include <string>

#define MAX_BONE_INFLUENCE 4

namespace PianoCore {
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    // bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    // weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};
struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};
}  // namespace PianoCore