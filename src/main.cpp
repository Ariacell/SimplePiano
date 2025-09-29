#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <engine/GLFWWindow.h>
#include <engine/RendererFactory.h>
#include <engine/application/ApplicationConstants.h>
#include <engine/application/ApplicationState.h>
#include <engine/audio/audio.h>
#include <engine/debug/debugUI.h>
#include <engine/shaders/OpenGlShader.h>
#include <game/components/Mesh.h>
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <util/timer.h>

#include <filesystem>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "engine/application/Application.h"
#include "engine/graphics/VertexArray.h"
#include "engine/input/InputManager.h"
#include "game/components/GameObject.h"
#include "game/components/Model.h"
#include "game/components/ModelComponent.h"

class PianoApp {
public:
    DebugUiLayer debugUi;
    RendererFactory rendererFactory;

    Camera mainSceneCamera;

    void run() {
        Ptr<PianoCore::Application> pianoApp = PianoCore::Application::Create();

        Engine::IWindow& window =
            *pianoApp.get()->GetApplicationState()->mainWindow;

        // TODO: This shouldn't be necessary. Very smelly and probably means
        // I've fuckyduckied my interface somewhat.
        GLFWwindow* glfwWindow =
            static_cast<GLFWwindow*>(pianoApp.get()
                                         ->GetApplicationState()
                                         ->mainWindow->GetNativeHandle());

        auto debugWindowData = &pianoApp.get()
                                    ->GetApplicationState()
                                    ->debugState.mainDebugWindowData;
        debugUi.init(glfwWindow, debugWindowData, &mainSceneCamera);
        pianoApp.get()->GetInput()->bindDebugSettings(debugWindowData);

        std::cout << ("Finished Init Input and DebugUi\n");

        auto renderer = rendererFactory.CreateRenderer(RendererType::OpenGL);
        renderer->Initialize(window);
        std::shared_ptr<Shaders::IShader> openGlShader =
            std::make_shared<Shaders::OpenGlShader>("something", "something");

        std::cout << "Starting main application loop\n" << std::endl;

        pianoApp.get()->Start();

#pragma region Temporary setup for scene geometry, to remove once Scene abstraction is ready
        Component::GameObject cloudObj;
        Component::GameObject cloudQuadObj;
        std::shared_ptr<Component::Material> cloudMat(
            new Component::Material(openGlShader, "path"));

        Component::Model ourModel("models/backpack/backpack.obj");
        std::shared_ptr<Component::Model> cubeOpenGlModel(
            new Component::Model(Component::MeshType::Cube));

        std::shared_ptr<Component::Model> quadOpenGlModel(
            new Component::Model(Component::MeshType::Quad));

        auto cloudCubeModel = cloudObj.AddComponent<Component::ModelComponent>(
            cubeOpenGlModel, openGlShader);
        auto cloudQuadModel =
            cloudQuadObj.AddComponent<Component::ModelComponent>(
                quadOpenGlModel, openGlShader);

#pragma endregion

        float frameTimeMs = 0.0f;

        while (!window.ShouldClose()) {
            auto frameStart = std::chrono::steady_clock::now();
            window.PollEvents();
            pianoApp.get()->UpdateToFrame();

            pianoApp.get()->GetApplicationState()->simulationTimer.TickTimer(
                [&]() {
                    // blah
                    //  Do physics/app state things
                    // std::cout << "Application Ticks so far: "
                    //           << appStateTimer.GetTickCount() << std::endl;
                    cloudObj.GetTransform()->translate(
                        glm::vec3(.05f, .0f, .0f));
                },
                5);

            // This probably doesn't need to be on a timer? Just want it to be
            // smooth but not sure if the 3rd person camera should be in app or
            // renderer yet
            pianoApp.get()->GetApplicationState()->framerateTimer.TickTimer(
                [&]() {
                    mainSceneCamera.ProcessInput(
                        pianoApp.get()->GetInput()->GetInputState(),
                        pianoApp.get()
                            ->GetApplicationState()
                            ->framerateTimer.GetTickSizeSeconds());
                    // std::cout << "Framerate time Ticks so far: "
                    //           << frameRateTimer.GetTickCount() << std::endl;
                },
                5);

#pragma region Rendering Logic
            debugUi.beginFrame();

            if (pianoApp.get()->GetInput()->isDebugWindowVisible()) {
                debugUi.renderDebugWindow(glfwWindow, debugWindowData,
                                          pianoApp.get()->GetApplicationState(),
                                          pianoApp.get()->GetInput());
            }

            renderer->SetWireframeRendering(
                debugWindowData->isWireframeRenderingEnabled);

            renderer->ClearScreen(0.1f, 0.1f, 0.1f, 1.0f);

            auto current_window_size = window.GetWindowSize();

            glm::mat4 view = glm::mat4(1.0f);
            view = glm::lookAt(mainSceneCamera.Position,
                               mainSceneCamera.Position + mainSceneCamera.Front,
                               mainSceneCamera.Up);
            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::perspective(
                glm::radians(45.0f),
                (float)current_window_size.x / (float)current_window_size.y,
                0.1f, 100.0f);

            // retrieve the matrix uniform locations and set up shaders

            unsigned int viewLoc =
                glGetUniformLocation(openGlShader.get()->GetID(), "view");
            unsigned int projLoc =
                glGetUniformLocation(openGlShader.get()->GetID(), "projection");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

            renderer->DrawObject(&cloudObj);
            renderer->DrawObject(&cloudQuadObj);
            // Cube broken due to vertex order but doesn't really matter, just a
            // counting issue the mechanics of reading in different objects are
            // working! renderer->DrawObject(&cubeObj);

            debugUi.endFrame();
            renderer->Present();
            pianoApp.get()->GetInput()->EndFrame();

            auto frameEnd = std::chrono::steady_clock::now();
            frameTimeMs =
                std::chrono::duration<float>(frameEnd - frameStart).count() *
                1000;

            auto targetFrameTimeMs = pianoApp.get()
                                         ->GetApplicationState()
                                         ->framerateTimer.GetTickSizeSeconds();
            if (frameTimeMs < targetFrameTimeMs) {
                float sleepTimeMs = targetFrameTimeMs - frameTimeMs;
                std::this_thread::sleep_for(
                    std::chrono::duration<float, milli>(sleepTimeMs));
            }
            // cout << "Current FPS: " << to_string(1.0f / frameTimeMs * 1000)
            //      << endl;
#pragma endregion Rendering Logic
        }
    }
};

int main() {
    PianoApp app;
    app.run();
}