#define GLFW_INCLUDE_NONE
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <audio/audio.h>
#include <input/input.h>
#include <ui/debugUI.h>
#include <ui/contants.h>
#include <shaders/openGlShaders.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <rendering/opengl/triangle.h>
#include <rendering/shapes.h>

Input::InputManager inputManager;

void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        return;
    }
    inputManager.keyCallback(key, action);
}

class PianoApp
{
public:
    Audio::AudioManager audioManager;
    DebugUiLayer debugUi;
    OpenGlShaders openGlShaders;
    Shapes shapes;

    void run()
    {
        auto *window = initWindow();
        std::cout << ("Finished Init Window\n");
        audioManager.initAudio();
        std::cout << ("Finished Init Audio\n");
        debugUi.init(window);
        std::cout << ("Finished Init DebugUi\n");

        auto shaderProgram = openGlShaders.loadShaders();

        unsigned int triangleVAO = OpenGlRenderer::bindTriangle(shapes.getTriangleData());

        while (!glfwWindowShouldClose(window))
        {
            debugUi.beginFrame();
            glClearColor(1.f, 0.f, 1.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwPollEvents();

            if (inputManager.isDebugWindowVisible())
            {
                debugUi.renderDebugWindow(window);
            }

            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shaderProgram);
            glBindVertexArray(triangleVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            debugUi.endFrame();
            glfwSwapBuffers(window);
        }
    }

private:
    GLFWwindow *initWindow()
    {
        int major, minor, rev;
        glfwGetVersion(&major, &minor, &rev);

        printf("GLFW version: %d.%d.%d\n", major, minor, rev);
        if (!glfwInit())
        {
            const char *description;
            glfwGetError(&description);
            fprintf(stderr, "GLFW Error: %s\n", description);
            throw std::runtime_error("Failed to init GLFW");
        }
        GLFWwindow *window = glfwCreateWindow(ui::WINDOW_DEFAULTS::WINDOW_WIDTH, ui::WINDOW_DEFAULTS::WINDOW_HEIGHT, "SimplePiano", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwSetWindowSizeLimits(window, 200, 200, GLFW_DONT_CARE, GLFW_DONT_CARE);

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
        std::cout << "Loaded GLAD" << std::endl;

        // Set the viewport for OpenGL to match our GLFW Window
        glViewport(0, 0, ui::WINDOW_DEFAULTS::WINDOW_WIDTH, ui::WINDOW_DEFAULTS::WINDOW_HEIGHT);

        // Set up input callbacks (only one for now, need to confirm how I want to decouple the input manager)
        glfwSetKeyCallback(window, glfwKeyCallback);

        return window;
    }
};

int main()
{

    PianoApp app;

    app.run();
    // std::cout<<("Hello World");
}