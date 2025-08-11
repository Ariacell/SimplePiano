#include <engine/OpenGlRenderer.h>

#include <filesystem>
#include <iostream>

/// @brief Initialise the OpenGL window (must occur after window is created)
/// @param window
void OpenGlRenderer::Initialize(Engine::IWindow* window) {
    this->window = window;
    using GLProcAddress = void* (*)(const char*);
    auto loader =
        reinterpret_cast<GLProcAddress>(window->GetWindowProcAddress());
    if (!gladLoadGLLoader(loader)) {
        throw std::runtime_error("Failed to load OpenGl via Glad for window");
    }
    this->rectangleVAO =
        OpenGlGraphics::bindRectangle(shapes.getSampleRectangleData());
    this->cubeVAO = OpenGlGraphics::bindCube(shapes.getSampleCubeVerts());

    printf("Vendor graphic card: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version GL: %s\n", glGetString(GL_VERSION));
    printf("Version GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    std::cout << "OpenGL context initialized\n";
    LoadRectangleTexture();

    glViewport(0, 0, 800, 600);  // example values
}

void OpenGlRenderer::ClearScreen(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGlRenderer::DrawObject(const int& vertexArray, const int& indexBuffer,
                                const Shaders::IShader& shader) const {
    glBindVertexArray(
        vertexArray);  // seeing as we only have a single VAO there's
                       // no need to bind it every time, but we'll do
                       // so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, indexBuffer, GL_UNSIGNED_INT, 0);
}

void OpenGlRenderer::DrawRectangle() {
    glBindTexture(GL_TEXTURE_2D, rectangleTexture);
    glBindVertexArray(
        this->rectangleVAO);  // seeing as we only have a single VAO there's
                              // no need to bind it every time, but we'll do
                              // so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // Do more fun things here once I have time.
}

void OpenGlRenderer::DrawCube() {
    glBindVertexArray(
        this->cubeVAO);  // seeing as we only have a single VAO there's no
                         // need to bind it every time, but we'll do so to
                         // keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // Do more fun things here once I have time.
}

void OpenGlRenderer::LoadRectangleTexture() {
    namespace fs = std::filesystem;

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D,
                  texture);  // all upcoming GL_TEXTURE_2D operations now
                             // have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT);  // set texture wrapping to GL_REPEAT
                                 // (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    std::string texturesPath =
        fs::current_path().string() + std::string("/textures");
    std::string filename = "/sky.jpg";
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load((texturesPath + "/" + filename).c_str(),
                                    &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        this->rectangleTexture = texture;
    } else {
        std::cout << "Failed to load texture " << filename << std::endl;
        std::cout << "Similar textures found: " << std::endl;
        for (const auto& entry : fs::directory_iterator(texturesPath))
            std::cout << entry.path() << std::endl;

        std::cout << stbi_failure_reason() << std::endl;
    }
    stbi_image_free(data);
}

void OpenGlRenderer::Present() {
    if (!window) {
        throw std::runtime_error(
            "Attempted to present OpenGL rendered scene without a handle "
            "to a running window!");
    }
    window->SwapBuffers();
}
