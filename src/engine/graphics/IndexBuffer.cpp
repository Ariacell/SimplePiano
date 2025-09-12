#include "IndexBuffer.h"

#include <glad/glad.h>

Renderer::IndexBuffer::IndexBuffer(IndexBufferData bufferData)
    : indiceCount(bufferData.count) {
    glGenBuffers(1, &associatedRendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, associatedRendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 bufferData.count * sizeof(unsigned int), bufferData.data,
                 GL_STATIC_DRAW);
}

Renderer::IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &associatedRendererId);
}

void Renderer::IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, associatedRendererId);
}

void Renderer::IndexBuffer::UnBind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
