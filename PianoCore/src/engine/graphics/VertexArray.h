#pragma once
#include <engine/graphics/VertexBuffer.h>
#include <engine/graphics/VertexBufferLayout.h>

namespace PianoCore {

class VertexArray {
private:
    unsigned associatedRendererId;

public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& data, const VertexBufferLayout& layout);

    void Bind() const;
    void UnBind() const;

    inline const unsigned int GetRendererId() {
        return associatedRendererId;
    }
};
}  // namespace PianoCore