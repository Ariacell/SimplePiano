#include "graphics/VertexBuffer.h"

#include <glad/glad.h>

PianoCore::VertexBuffer::VertexBuffer(VertexBufferData bufferData) {
    glGenBuffers(1, &associatedRendererId);
    glBindBuffer(GL_ARRAY_BUFFER, associatedRendererId);
    glBufferData(GL_ARRAY_BUFFER, bufferData.size, bufferData.data,
                 GL_STATIC_DRAW);
}

PianoCore::VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &associatedRendererId);
}

void PianoCore::VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, associatedRendererId);
}

void PianoCore::VertexBuffer::UnBind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
