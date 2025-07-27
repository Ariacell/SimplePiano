#define GLFW_INCLUDE_NONE
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <audio/audio.h>
#include <engine/debug/debugUI.h>
#include <ui/contants.h>
#include <shaders/OpenGlShader.h>
#include <engine/RendererFactory.h>
#include <engine/GLFWWindow.h>
#include <appstate.h>
#include <util/timer.h>
#include "engine/input/InputManager.h"

// static void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
// {
//     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//     {
//         glfwSetWindowShouldClose(window, true);
//         return;
//     }
//     Input::InputManager *handler = reinterpret_cast<Input::InputManager *>(glfwGetWindowUserPointer(window));
//     if (handler)
//         handler->keyCallback(key, action, mods);
// }

class PianoApp
{
public:
    Audio::AudioManager audioManager;
    DebugUiLayer debugUi;
    RendererFactory rendererFactory;

    State::ApplicationState appState;

    Camera mainSceneCamera;

    void run()
    {
        // Todo: figure out if this is really the cleanest way to create this window class...
        auto window = std::make_unique<PianoGLFWWindow>();
        window->Create(ui::WINDOW_DEFAULTS::WINDOW_WIDTH, ui::WINDOW_DEFAULTS::WINDOW_HEIGHT, "SimplePiano");
        GLFWwindow *glfwWindow = (GLFWwindow *)(window->GetNativeHandle());
        std::cout << ("Finished Init Window\n");

        Input::InputManager inputManager(window.get(), &mainSceneCamera);
        audioManager.initAudio();
        std::cout << ("Finished Init Audio\n");

        auto debugWindowData = &appState.debugState.mainDebugWindowData;
        debugUi.init(glfwWindow, debugWindowData, &mainSceneCamera);
        inputManager.bindDebugSettings(debugWindowData);

        std::cout << ("Finished Init Input and DebugUi\n");

        auto renderer = rendererFactory.CreateRenderer(RendererType::OpenGL);
        renderer->Initialize(window.get());
        auto openGlShader = Shaders::OpenGlShader("something", "something");

        std::cout << "Starting main application loop\n"
            << std::endl;

        Util::Timer appStateTimer;
        float appStateTickRate = 0.033f;
        appStateTimer.Init(appStateTickRate);

        Util::Timer frameRateTimer;
        float frameRateTargetTickRate = 0.003f;
        frameRateTimer.Init(frameRateTargetTickRate);

        while (!window->ShouldClose())
        {
            window->PollEvents();

            // Note both this is currently greedy with no upper bound on the physics catchup ticks, would definitely be an issue for clients that start lagging behind
            // App updates
            if (appStateTimer.GetElapsedTimeSinceLastTick() > appStateTickRate)
            {
                appStateTimer.TickTimer(); // Todo: this should actually compensate for the overflow from the tickrate but good enough for now
                // Do physics/app state things
            }

            // Since the physics update is greedy, this can probably not be greedy? but I just want to experiment with things working first.
            // Rendering the updated app at the decoupled target framerate (hopefully haHA, arithmetic is hard)
            if (frameRateTimer.GetElapsedTimeSinceLastTick() > frameRateTargetTickRate)
            {
                frameRateTimer.TickTimer();
                // Render whatever the app state is, maybe some fancy interpolation here later

                debugUi.beginFrame();
                glClearColor(1.f, 0.f, 1.f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                if (inputManager.isDebugWindowVisible())
                {
                    debugUi.renderDebugWindow(glfwWindow, debugWindowData, &appState, &inputManager);
                }

                int display_w, display_h;
                glfwGetFramebufferSize(glfwWindow, &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);
                glPolygonMode(GL_FRONT_AND_BACK, debugWindowData->isWireframeRenderingEnabled ? GL_LINE : GL_FILL);

                renderer->ClearScreen(0.1f, 0.1f, 0.1f, 1.0f);

                auto current_window_size = window.get()->GetWindowSize();
                openGlShader.use();
                // glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                // glm::mat4 projection = glm::mat4(1.0f);
                // projection = glm::perspective(glm::radians(45.0f), (float)current_window_size.x / (float)current_window_size.y, 0.1f, 100.0f);
                // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
                renderer->DrawRectangle();
                // renderer->DrawCube();

                debugUi.endFrame();
                renderer->Present();
                inputManager.EndFrame();
            }
        }
    }
};

int main()
{
    PianoApp app;
    app.run();
}