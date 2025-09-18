#pragma once

namespace PianoCore {
struct VertexBufferData {
    const void* data;
    unsigned int size;
};

class VertexBuffer {
private:
    unsigned associatedRendererId;

public:
    VertexBuffer(VertexBufferData bufferData);
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};
}  // namespace Renderer