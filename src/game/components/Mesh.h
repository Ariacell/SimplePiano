#pragma once

#include <engine/graphics/IndexBuffer.h>
#include <engine/graphics/VertexArray.h>
#include <engine/graphics/VertexBuffer.h>
#include <engine/graphics/VertexBufferLayout.h>

#include <iostream>
#include <string>

#include "Component.h"
namespace Component {

class Mesh {
public:
    Mesh(Renderer::VertexArray* va, Renderer::VertexBufferArgs vertexBufferData,
         Renderer::IndexBufferArgs indexBufferData,
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
}  // namespace Component