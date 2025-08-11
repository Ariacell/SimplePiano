#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <application/contants.h>
#include <appstate.h>
#include <engine/GLFWWindow.h>
#include <engine/RendererFactory.h>
#include <engine/audio/audio.h>
#include <engine/debug/debugUI.h>
#include <engine/shaders/OpenGlShader.h>
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <util/timer.h>

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <thread>

#include "engine/input/InputManager.h"

class PianoApp {
public:
    Audio::AudioManager audioManager;
    DebugUiLayer debugUi;
    RendererFactory rendererFactory;

    State::ApplicationState appState, priorAppState;

    Camera mainSceneCamera;

    void run() {
        // Todo: figure out if this is really the cleanest way to create this
        // window class...
        auto window = std::make_unique<PianoGLFWWindow>();
        window->Create(Application::WINDOW_DEFAULTS::WINDOW_WIDTH,
                       Application::WINDOW_DEFAULTS::WINDOW_HEIGHT,
                       "SimplePiano");
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

        std::cout << "Starting main application loop\n" << std::endl;

        Util::Timer appStateTimer;
        float appStateTickRateMs = 31.25f;
        appStateTimer.Init(appStateTickRateMs);

        Util::Timer frameRateTimer;
        float targetFramerate = 70.0f;
        float targetFrameTimeMs = (1 / targetFramerate) * 1000;
        frameRateTimer.Init(targetFrameTimeMs);

        while (!window->ShouldClose()) {
            auto frameStart = std::chrono::steady_clock::now();
            window->PollEvents();

            // Note both this is currently greedy with no upper bound on the
            // physics catchup ticks, would definitely be an issue for clients
            // that start lagging behind App updates
            appStateTimer.Update();
            frameRateTimer.Update();
            priorAppState = appState;

            appStateTimer.TickTimer(
                [&]() {
                    // blah
                    //  Do physics/app state things
                    std::cout << "Application Ticks so far: "
                              << appStateTimer.GetTickCount() << std::endl;
                },
                5);  // Todo: this should actually compensate for the overflow
            // from the tickrate but good enough for now

            // This probably doesn't need to be on a timer? Just want it to be
            // smooth but not sure if the 3rd person camera should be in app or
            // renderer yet
            frameRateTimer.TickTimer(
                [&]() {
                    mainSceneCamera.ProcessInput(inputManager.GetInputState(),
                                                 frameRateTimer.GetTickSize());
                    std::cout << "Framerate time Ticks so far: "
                              << frameRateTimer.GetTickCount() << std::endl;
                },
                5);

#pragma region Rendering Logic
            debugUi.beginFrame();
            glClearColor(1.f, 0.f, 1.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (inputManager.isDebugWindowVisible()) {
                debugUi.renderDebugWindow(glfwWindow, debugWindowData,
                                          &appState, &inputManager);
            }

            int display_w, display_h;
            glfwGetFramebufferSize(glfwWindow, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glPolygonMode(GL_FRONT_AND_BACK,
                          debugWindowData->isWireframeRenderingEnabled
                              ? GL_LINE
                              : GL_FILL);

            renderer->ClearScreen(0.1f, 0.1f, 0.1f, 1.0f);

            auto current_window_size = window.get()->GetWindowSize();
            openGlShader.use();

            glm::mat4 model = glm::mat4(1.0f);
            model =
                glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f),
                            glm::vec3(0.5f, 1.0f, 0.0f));
            glm::mat4 view = glm::mat4(1.0f);  // make sure to initialize matrix
            // to identity matrix first
            // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            view = glm::lookAt(mainSceneCamera.Position,
                               mainSceneCamera.Position + mainSceneCamera.Front,
                               mainSceneCamera.Up);
            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::perspective(
                glm::radians(45.0f),
                (float)current_window_size.x / (float)current_window_size.y,
                0.1f, 100.0f);

            glEnable(GL_DEPTH_TEST);
            // retrieve the matrix uniform locations
            unsigned int modelLoc =
                glGetUniformLocation(openGlShader.GetID(), "model");
            unsigned int viewLoc =
                glGetUniformLocation(openGlShader.GetID(), "view");
            unsigned int projLoc =
                glGetUniformLocation(openGlShader.GetID(), "projection");
            // pass them to the shaders (3 different ways)
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
            // note: currently we set the projection matrix each frame, but
            // since the projection matrix rarely changes it's often best
            // practice to set it outside the main loop only once.
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

            renderer->DrawRectangle();
            // renderer->DrawCube();
            debugUi.endFrame();
            renderer->Present();
            inputManager.EndFrame();

            auto frameEnd = std::chrono::steady_clock::now();
            float frameTimeMs =
                std::chrono::duration<float>(frameEnd - frameStart).count() *
                1000;

            if (frameTimeMs < targetFrameTimeMs) {
                float sleepTimeMs = targetFrameTimeMs - frameTimeMs;
                std::this_thread::sleep_for(
                    std::chrono::duration<float, milli>(sleepTimeMs));
            }
            cout << "Current FPS: " << to_string(1.0f / frameTimeMs * 1000)
                 << endl;
#pragma endregion Rendering Logic
        }
    }
};

int main() {
    PianoApp app;
    app.run();
}