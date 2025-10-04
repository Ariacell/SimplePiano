#pragma once
#include <string>

namespace Shaders {
class IShader {
public:
    unsigned int ID;
    IShader(){};

    virtual ~IShader(){};

    /// @brief Used for binding the shader
    virtual void use() = 0;
    virtual void reload() = 0;

    virtual void setFloat(const std::string &name, float value) const = 0;

    unsigned int GetID() {
        return ID;
    }
};
}  // namespace Shaders
