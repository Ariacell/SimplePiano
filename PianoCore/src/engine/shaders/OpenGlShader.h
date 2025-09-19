#include <GL/gl.h>

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
    void setFloat(const std::string& name, float value) const override;
    unsigned int GetID() {
        return ID;
    }

private:
    unsigned int loadShader();
    GLuint CompileShader(GLuint type, const std::string& source);
    unsigned int compileVertexShaders();
    unsigned int compileFragmentShaders();
    unsigned int LinkShader(unsigned int vertexShader,
                            unsigned int fragmentShader);
};
}  // namespace Shaders