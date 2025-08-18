#include "Mesh.h"

Component::Mesh::Mesh(Renderer::VertexBuffer vertexBuffer,
                      Renderer::IndexBuffer indexBuffer,
                      Renderer::VertexBufferLayout layout) {
    vertexBuffer = vertexBuffer;
    indexBuffer = indexBuffer;
    layout = layout;
}

Renderer::VertexBuffer Component::Mesh::GetVertexBuffer() {
    return vertexBuffer;
}
Renderer::IndexBuffer Component::Mesh::GetIndexBuffer() {
    return indexBuffer;
}
Renderer::VertexBufferLayout Component::Mesh::GetBufferLayout() {
    return layout;
}
