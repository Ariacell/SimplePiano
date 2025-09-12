#include "VertexBuffer.h"

#include <glad/glad.h>

Renderer::VertexBuffer::VertexBuffer(VertexBufferData bufferData) {
    glGenBuffers(1, &associatedRendererId);
    glBindBuffer(GL_ARRAY_BUFFER, associatedRendererId);
    glBufferData(GL_ARRAY_BUFFER, bufferData.size, bufferData.data,
                 GL_STATIC_DRAW);
}

Renderer::VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &associatedRendererId);
}

void Renderer::VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, associatedRendererId);
}

void Renderer::VertexBuffer::UnBind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
