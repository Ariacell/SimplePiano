#pragma once

namespace Renderer {
struct VertexBufferArgs {
    const void* data;
    unsigned int size;
};

class VertexBuffer {
private:
    unsigned associatedRendererId;

public:
    VertexBuffer(VertexBufferArgs bufferData);
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};
}  // namespace Renderer