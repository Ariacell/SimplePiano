#pragma once

namespace Renderer {

struct IndexBufferData {
    const unsigned int* data;
    unsigned int count;
};

class IndexBuffer {
private:
    unsigned associatedRendererId;
    unsigned indiceCount;

public:
    IndexBuffer(IndexBufferData bufferData);
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    const int GetIndiceCount() const {
        return indiceCount;
    }
};
}  // namespace Renderer