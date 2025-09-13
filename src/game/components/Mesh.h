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
    Mesh1(Renderer::VertexArray* va,
          Renderer::VertexBufferData vertexBufferData,
          Renderer::IndexBufferData indexBufferData,
          Renderer::VertexBufferLayout layout);

    Renderer::VertexArray* GetVertexArray();
    Renderer::VertexBuffer* GetVertexBuffer();
    Renderer::IndexBuffer* GetIndexBuffer();
    Renderer::VertexBufferLayout* GetBufferLayout();

private:
    Renderer::VertexArray* vertexArray;
    Renderer::VertexBuffer vertexBuffer;
    Renderer::IndexBuffer indexBuffer;
    Renderer::VertexBufferLayout layout;
};

struct SubMesh {
    PianoCore::Buffer<Renderer::Vertex> Vertices;
    PianoCore::Buffer<uint32_t> Indices;
    uint32_t MaterialIndex;
};

class Mesh {
public:
    // mesh data
    std::vector<Renderer::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Renderer::Texture> textures;

    Mesh(MeshType type) : Type(type) {
    }
    ~Mesh() = default;

    Mesh(std::vector<Renderer::Vertex> vertices,
         std::vector<unsigned int> indices,
         std::vector<Renderer::Texture> textures);
    Ref<Mesh> Create(MeshType type, const Material& material);
    Ref<Mesh> Create(MeshType type,
                     PianoCore::Buffer<Renderer::Vertex>&& vertices,
                     PianoCore::Buffer<uint32_t>&& indices,
                     const Material& material);

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