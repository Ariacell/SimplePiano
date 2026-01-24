#pragma once
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>

#include "IShader.h"

namespace Shaders {
class OpenGlShader : public IShader {
public:
    /// @brief compiles and links OpenGL shaders
    /// @return The shader program ID from the loaded shaders for use in OpenGL
    /// render pipeline

    OpenGlShader(const char* vertexPath, const char* fragmentPath);
    void use() override;
    void reload() override;
    void setFloat(const std::string& name, float value) const override;
    unsigned int GetID() {
        return ID;
    }

private:
    unsigned int loadShader(const char* vertexPath, const char* fragmentPath);
    GLuint CompileShader(GLuint type, const std::string& source);
    unsigned int compileVertexShaders(const char* vertexShaderFilePath);
    unsigned int compileFragmentShaders(const char* fragmentShaderFilePath);
    unsigned int LinkShader(unsigned int vertexShader,
                            unsigned int fragmentShader);

    const char* vertFilePath;
    const char* fragFilePath;
};
}  // namespace Shaders