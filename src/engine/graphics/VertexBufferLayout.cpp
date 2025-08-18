#include "VertexBufferLayout.h"
namespace Renderer {
template <>
void Renderer::VertexBufferLayout::Push<float>(unsigned int count) {
    VertexBufferElement el = {GL_FLOAT, count, false};
    elements.push_back(el);
    stride += 4;
}

template <>
void Renderer::VertexBufferLayout::Push<unsigned int>(unsigned int count) {
    VertexBufferElement el = {GL_UNSIGNED_INT, count, false};
    elements.push_back(el);
    stride += 4;
}

template <>
void Renderer::VertexBufferLayout::Push<unsigned char>(unsigned int count) {
    VertexBufferElement el = {GL_UNSIGNED_BYTE, count, true};
    elements.push_back(el);
    stride += 1;
}
}  // namespace Renderer