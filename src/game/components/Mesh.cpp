#include "Mesh.h"

Component::Mesh::Mesh(Renderer::VertexArray* va,
                      Renderer::VertexBufferArgs vertexBufferData,
                      Renderer::IndexBufferArgs indexBufferData,
                      Renderer::VertexBufferLayout layout)
    : vertexBuffer(vertexBufferData),
      indexBuffer(indexBufferData),
      layout(layout) {
    vertexArray = va;
    va->Bind();
    std::cout << "Bound VAO ID: " << va->GetRendererId() << std::endl;
    va->AddBuffer(vertexBuffer, layout);
    indexBuffer.Bind();
    std::cout << "Bound mesh to VAO ID: " << va->GetRendererId() << std::endl;
}

Renderer::VertexArray* Component::Mesh::GetVertexArray() {
    return vertexArray;
}

Renderer::VertexBuffer* Component::Mesh::GetVertexBuffer() {
    return &vertexBuffer;
}
Renderer::IndexBuffer* Component::Mesh::GetIndexBuffer() {
    return &indexBuffer;
}
Renderer::VertexBufferLayout* Component::Mesh::GetBufferLayout() {
    return &layout;
}
