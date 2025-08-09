#define GLFW_INCLUDE_NONE
#include <iostream>
#include <thread>
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
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

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

    State::ApplicationState appState, priorAppState;

    Camera mainSceneCamera;

    void run()
    {
        // Todo: figure out if this is really the cleanest way to create this window class...
        auto window = std::make_unique<PianoGLFWWindow>();
        window->Create(ui::WINDOW_DEFAULTS::WINDOW_WIDTH, ui::WINDOW_DEFAULTS::WINDOW_HEIGHT, "SimplePiano");
        GLFWwindow* glfwWindow = (GLFWwindow*)(window->GetNativeHandle());
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
        float appStateTickRateMs = 31.25f;
        // float appStateTickRate = 31250000.0f; // 32*X nanoseconds into each second
        appStateTimer.Init(appStateTickRateMs);

        Util::Timer frameRateTimer;
        // float frameRateTargetTickRate = 800000.0f; // ~120*X nanoseconds into each second
        float targetFramerate = 60.0f; // ~120*X nanoseconds into each second
        float targetFrameTime = 1 / targetFramerate; // ~120*X nanoseconds into each second
        frameRateTimer.Init(targetFrameTime);

        while (!window->ShouldClose())
        {
            auto frameStart = std::chrono::steady_clock::now();
            window->PollEvents();


            // Note both this is currently greedy with no upper bound on the physics catchup ticks, would definitely be an issue for clients that start lagging behind
            // App updates
            appStateTimer.Update();
            frameRateTimer.Update();
            priorAppState = appState;

            appStateTimer.TickTimer([&]() {
                //blah
                // Do physics/app state things
                std::cout << "Application Ticks so far: " << appStateTimer.GetTickCount() << std::endl;
            }, 5); // Todo: this should actually compensate for the overflow from the tickrate but good enough for now
            
            
            // This probably doesn't need to be on a timer? Just want it to be smooth but not sure if the 3rd person camera should be in app or renderer yet
            frameRateTimer.TickTimer([&]() {
                mainSceneCamera.ProcessInput(inputManager.GetInputState(), appStateTimer.GetTickSize());
                std::cout << "Framerate time Ticks so far: " << appStateTimer.GetTickCount() << std::endl;
            }, 5);

            #pragma region Rendering Logic 
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

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            view = glm::lookAt(mainSceneCamera.Position, mainSceneCamera.Position + mainSceneCamera.Front, mainSceneCamera.Up);
            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::perspective(glm::radians(45.0f), (float)current_window_size.x / (float)current_window_size.y, 0.1f, 100.0f);

            glEnable(GL_DEPTH_TEST);
            // retrieve the matrix uniform locations
            unsigned int modelLoc = glGetUniformLocation(openGlShader.GetID(), "model");
            unsigned int viewLoc = glGetUniformLocation(openGlShader.GetID(), "view");
            unsigned int projLoc = glGetUniformLocation(openGlShader.GetID(), "projection");
            // pass them to the shaders (3 different ways)
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
            // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);


            // renderer->DrawRectangle();
            renderer->DrawCube();
            debugUi.endFrame();
            renderer->Present();
            inputManager.EndFrame();

            auto frameEnd = std::chrono::steady_clock::now();
            float frameTime = std::chrono::duration<float>(frameEnd - frameStart).count();

            if (frameTime < targetFrameTime) {
                float sleepTime = targetFrameTime - frameTime;
                std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
            }
            #pragma endregion Rendering Logic
        }
    }
};

int main()
{
    PianoApp app;
    app.run();
}