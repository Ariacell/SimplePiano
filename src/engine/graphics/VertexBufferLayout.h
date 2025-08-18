#pragma once
#include <assert.h>
#include <glad/glad.h>

#include <vector>

namespace Renderer {

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalised;

    static unsigned int GetSizeOfElementType(unsigned int type) {
        switch (type) {
            case GL_FLOAT:
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
        }
        assert(
            (void("Unable to determine size of vertex buffer element"), false));
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;

public:
    VertexBufferLayout() : stride(0) {
    }

    template <typename T>
    void Push(unsigned int count) {
    }

    inline const std::vector<VertexBufferElement> GetElements() const& {
        return elements;
    }
    inline unsigned int GetStride() const {
        return stride;
    }
};
}  // namespace Renderer