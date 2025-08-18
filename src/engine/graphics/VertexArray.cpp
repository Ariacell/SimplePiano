#include "VertexArray.h"

#include <glad/glad.h>

Renderer::VertexArray::VertexArray() {
    glGenVertexArrays(1, &associatedRendererId);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s),
    // and then configure vertex attributes(s).
    glBindVertexArray(associatedRendererId);
}

void Renderer::VertexArray::AddBuffer(const VertexBuffer& data,
                                      const VertexBufferLayout& layout) {
    // Bind();
    // data.Bind();
    // const auto& elements = layout.GetElements();
    // unsigned int offset = 0;
    // for (unsigned int i = 0; i < elements.size(); i++) {
    //     const auto& element = elements[i];
    //     glEnableVertexAttribArray(i);
    //     glVertexAttribPointer(i, element.count, element.type,
    //     element.normalised, layout.GetStride(),
    //                       (const void*)offset);
    //     offset += element.count;
    // }
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

Renderer::VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &associatedRendererId);
}

void Renderer::VertexArray::Bind() const {
    glBindVertexArray(associatedRendererId);
}

void Renderer::VertexArray::UnBind() const {
    glBindVertexArray(0);
}
