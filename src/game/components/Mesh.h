#pragma once

#include <engine/core/buffer.h>
#include <engine/core/list.h>
#include <engine/core/pointer.h>
#include <engine/graphics/IndexBuffer.h>
#include <engine/graphics/Structures.h>
#include <engine/graphics/VertexArray.h>
#include <engine/graphics/VertexBuffer.h>
#include <engine/graphics/VertexBufferLayout.h>
#include <engine/shaders/IShader.h>

#include <iostream>
#include <string>
#include <vector>

#include "Component.h"
#include "Material.h"
namespace Component {

enum class MeshType { Cube, Quad, Model };

class Mesh1 {
public:
    Mesh1(PianoCore::VertexArray* vertexArray,
          PianoCore::VertexBufferData vertexBufferData,
          PianoCore::IndexBufferData indexBufferData,
          PianoCore::VertexBufferLayout layout);

    PianoCore::VertexArray* GetVertexArray();
    PianoCore::VertexBuffer* GetVertexBuffer();
    PianoCore::IndexBuffer* GetIndexBuffer();
    PianoCore::VertexBufferLayout* GetBufferLayout();

private:
    PianoCore::VertexArray* vertexArray;
    PianoCore::VertexBuffer vertexBuffer;
    PianoCore::IndexBuffer indexBuffer;
    PianoCore::VertexBufferLayout layout;
};

struct SubMesh {
    std::vector<PianoCore::Vertex> Vertices;
    std::vector<uint32_t> Indices;
    uint32_t MaterialIndex;
};

class Mesh {
public:
    // mesh data
    std::vector<PianoCore::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<PianoCore::Texture> textures;

    Mesh(MeshType type) : Type(type) {
    }
    ~Mesh() = default;

    Mesh(std::vector<PianoCore::Vertex> vertices,
         std::vector<unsigned int> indices,
         std::vector<PianoCore::Texture> textures);
    Ref<Mesh> Create(MeshType type, const Material& material);
    Ref<Mesh> Create(MeshType type, std::vector<PianoCore::Vertex>&& vertices,
                     std::vector<uint32_t>&& indices, const Material& material);

    void Draw(const std::shared_ptr<Shaders::IShader>& shader);

private:
    //  render data
    unsigned int VAO, VBO, EBO;

    const MeshType Type;
    PianoCore::List<SubMesh> SubMeshes;
    PianoCore::List<Material> Materials;
    void setupMesh();
};
}  // namespace Component