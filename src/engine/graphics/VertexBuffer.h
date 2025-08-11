#pragma once

namespace Renderer {

class VertexBuffer {
private:
    unsigned associatedRendererId;

public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};
}  // namespace Renderer