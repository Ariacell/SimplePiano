#pragma once

namespace Renderer {

class IndexBuffer {
private:
    unsigned associatedRendererId;
    unsigned indiceCount;

public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;
};
}  // namespace Renderer