#include "VertexArray.h"

#include <glad/glad.h>

#include <iostream>

PianoCore::VertexArray::VertexArray() {
    glGenVertexArrays(1, &associatedRendererId);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL Error at callsite : " << std::hex << err
                  << std::endl;
    }
    glBindVertexArray(associatedRendererId);
}

void PianoCore::VertexArray::AddBuffer(const VertexBuffer& data,
                                      const VertexBufferLayout& layout) {
    Bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

PianoCore::VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &associatedRendererId);
}

void PianoCore::VertexArray::Bind() const {
    glBindVertexArray(associatedRendererId);
}

void PianoCore::VertexArray::UnBind() const {
    glBindVertexArray(0);
}
