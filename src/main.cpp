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
#include <graphics/opengl/triangle.h>
#include <graphics/shapes.h>
#include <engine/RendererFactory.h>
#include <memory>
#include <engine/GLFWWindow.h>

static void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        return;
    }
    Input::InputManager *handler = reinterpret_cast<Input::InputManager *>(glfwGetWindowUserPointer(window));
    if (handler)
        handler->keyCallback(key, action, mods);
}

class PianoApp
{
public:
    Audio::AudioManager audioManager;
    DebugUiLayer debugUi;
    OpenGlShaders openGlShaders;
    Shapes shapes;
    RendererFactory rendererFactory;

    debugUI::DebugLayerMainWindowData debugWindowData;

    void run()
    {
        // Todo: 
        auto window = std::make_unique<PianoGLFWWindow>();
        window->Create(ui::WINDOW_DEFAULTS::WINDOW_WIDTH, ui::WINDOW_DEFAULTS::WINDOW_HEIGHT, "SimplePiano");
        GLFWwindow *glfwWindow = (GLFWwindow*)(window->GetNativeHandle());
        std::cout << ("Finished Init Window\n");

        Input::InputManager inputManager(glfwWindow);
        audioManager.initAudio();
        std::cout << ("Finished Init Audio\n");

        debugUi.init(glfwWindow, &debugWindowData);
        inputManager.bindDebugSettings(&debugWindowData);
        std::cout << ("Finished Init DebugUi\n");

        auto renderer = rendererFactory.CreateRenderer(RendererType::OpenGL);
        renderer->Initialize(window.get());

        // WIP refactoring out all the glfw logic into the abstract window pattern
        glfwSetKeyCallback(glfwWindow, glfwKeyCallback);

        auto shaderProgram = openGlShaders.loadShaders();

        // unsigned int triangleVAO = OpenGlGraphics::bindRectangle(shapes.getSampleRectangleData());

        while (!window->ShouldClose())
        {
            debugUi.beginFrame();
            glClearColor(1.f, 0.f, 1.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            window->PollEvents();

            if (inputManager.isDebugWindowVisible())
            {
                debugUi.renderDebugWindow(glfwWindow, &debugWindowData);
            }

            int display_w, display_h;
            glfwGetFramebufferSize(glfwWindow, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glPolygonMode(GL_FRONT_AND_BACK, debugWindowData.isWireframeRenderingEnabled ? GL_LINE : GL_FILL);
            
            renderer->ClearScreen(0.1f, 0.1f, 0.1f, 1.0f);

            glUseProgram(shaderProgram);
            renderer->DrawRectangle();

            debugUi.endFrame();
            window->SwapBuffers();
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