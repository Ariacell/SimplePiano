#pragma once

namespace Renderer {

struct IndexBufferArgs {
    const unsigned int* data;
    unsigned int count;
};

class IndexBuffer {
private:
    unsigned associatedRendererId;
    unsigned indiceCount;

public:
    IndexBuffer(IndexBufferArgs bufferData);
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    const int GetIndiceCount() const {
        return indiceCount;
    }
};
}  // namespace Renderer