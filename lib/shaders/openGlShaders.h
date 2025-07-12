class OpenGlShaders
{
public:
    /// @brief compiles and links OpenGL shaders
    /// @return The shader program ID from the loaded shaders for use in OpenGL render pipeline 
    unsigned int loadShaders();

private:
    unsigned int compileVertexShaders();
    unsigned int compileFragmentShaders();
    unsigned int linkShaders(unsigned int vertexShader, unsigned int fragmentShader);
};