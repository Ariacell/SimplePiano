#pragma once

#include <engine/graphics/IndexBuffer.h>
#include <engine/graphics/VertexBuffer.h>
#include <engine/graphics/VertexBufferLayout.h>

#include <string>

#include "Component.h"
namespace Component {

class Mesh {
public:
    Mesh(Renderer::VertexBuffer vertexBuffer, Renderer::IndexBuffer indexBuffer,
         Renderer::VertexBufferLayout layout);

    Renderer::VertexBuffer GetVertexBuffer();
    Renderer::IndexBuffer GetIndexBuffer();
    Renderer::VertexBufferLayout GetBufferLayout();

private:
    Renderer::VertexBuffer vertexBuffer;
    Renderer::IndexBuffer indexBuffer;
    Renderer::VertexBufferLayout layout;
};
}  // namespace Component