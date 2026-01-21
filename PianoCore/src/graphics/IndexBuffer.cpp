#include "graphics/IndexBuffer.h"

#include <glad/glad.h>

PianoCore::IndexBuffer::IndexBuffer(IndexBufferData bufferData)
    : indiceCount(bufferData.count) {
    glGenBuffers(1, &associatedRendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, associatedRendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 bufferData.count * sizeof(unsigned int), bufferData.data,
                 GL_STATIC_DRAW);
}

PianoCore::IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &associatedRendererId);
}

void PianoCore::IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, associatedRendererId);
}

void PianoCore::IndexBuffer::UnBind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
