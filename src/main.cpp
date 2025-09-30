#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <engine/GLFWWindow.h>
#include <engine/RendererFactory.h>
#include <engine/application/ApplicationConstants.h>
#include <engine/application/ApplicationState.h>
#include <engine/audio/audio.h>
#include <engine/debug/debugUI.h>
#include <engine/graphics/OpenGLLine.h>
#include <engine/shaders/OpenGlShader.h>
#include <game/components/Mesh.h>
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <util/timer.h>

#include <filesystem>
#include <format>
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

    Camera mainSceneCamera;

    void run() {
        Ptr<PianoCore::Application> pianoApp = PianoCore::Application::Create();

        Engine::IWindow& window = *pianoApp->GetApplicationState()->mainWindow;

        // TODO: This shouldn't be necessary. Very smelly and probably means
        // I've fuckyduckied my interface somewhat.
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(
            pianoApp->GetApplicationState()->mainWindow->GetNativeHandle());

        auto* debugWindowData =
            &pianoApp->GetApplicationState()->debugState.mainDebugWindowData;
        debugUi.init(glfwWindow, debugWindowData, &mainSceneCamera);
        pianoApp->GetInput()->bindDebugSettings(debugWindowData);

        std::cout << ("Finished Init Input and DebugUi\n");

        std::shared_ptr<Shaders::IShader> openGlShader =
            std::make_shared<Shaders::OpenGlShader>("something", "something");

        std::cout << "Starting main application loop\n" << std::endl;

        pianoApp->Start();

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

        cloudObj.AddComponent<Component::ModelComponent>(cubeOpenGlModel,
                                                         openGlShader);
        cloudQuadObj.AddComponent<Component::ModelComponent>(quadOpenGlModel,
                                                             openGlShader);

#pragma endregion

        float frameTimeMs = 0.0F;

        while (!window.ShouldClose()) {
            auto frameStart = std::chrono::steady_clock::now();
            window.PollEvents();
            pianoApp->UpdateToFrame();

            pianoApp->GetApplicationState()->simulationTimer.TickTimer(
                [&]() {
                    // blah
                    //  Do physics/app state things
                    // std::cout << "Application Ticks so far: "
                    //           << appStateTimer.GetTickCount() << std::endl;
                    cloudObj.GetTransform()->translate(
                        glm::vec3(.05F, .0F, .0F));
                },
                5);

            // This probably doesn't need to be on a timer? Just want it to be
            // smooth but not sure if the 3rd person camera should be in app or
            // renderer yet
            pianoApp->GetApplicationState()->framerateTimer.TickTimer(
                [&]() {
                    mainSceneCamera.ProcessInput(
                        pianoApp->GetInput()->GetInputState(),
                        pianoApp->GetApplicationState()
                            ->framerateTimer.GetTickSizeSeconds());
                    // std::cout << "Framerate time Ticks so far: "
                    //           << frameRateTimer.GetTickCount() << std::endl;
                },
                5);

#pragma region Rendering Logic
            debugUi.beginFrame();

            if (pianoApp->GetInput()->isDebugWindowVisible()) {
                debugUi.renderDebugWindow(glfwWindow, debugWindowData,
                                          pianoApp->GetApplicationState(),
                                          pianoApp->GetInput());
            }

            pianoApp->GetRenderer()->SetWireframeRendering(
                debugWindowData->isWireframeRenderingEnabled);

            pianoApp->GetRenderer()->ClearScreen(0.1F, 0.1F, 0.1F, 1.0F);

            auto current_window_size = window.GetWindowSize();

            glm::mat4 view = glm::mat4(1.0F);
            view = glm::lookAt(mainSceneCamera.Position,
                               mainSceneCamera.Position + mainSceneCamera.Front,
                               mainSceneCamera.Up);
            glm::mat4 projection = glm::mat4(1.0F);
            projection = glm::perspective(
                glm::radians(45.0F),
                (float)current_window_size.x / (float)current_window_size.y,
                0.1F, 100.0F);

            // retrieve the matrix uniform locations and set up shaders
            openGlShader->use();
            unsigned int viewLoc =
                glGetUniformLocation(openGlShader->GetID(), "view");
            unsigned int projLoc =
                glGetUniformLocation(openGlShader->GetID(), "projection");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

            pianoApp->GetRenderer()->DrawObject(&cloudObj);
            pianoApp->GetRenderer()->DrawObject(&cloudQuadObj);

            // Playing with debug lines to start experimenting with raycasting
            // to the quad
            glm::vec2 windowSize =
                pianoApp->GetApplicationState()->mainWindow->GetWindowSize();
            glm::vec3 worldPos = glm::unProject(
                glm::vec3(
                    pianoApp->GetInput()->GetMousePosition().x,
                    windowSize.y - pianoApp->GetInput()->GetMousePosition().y,
                    0.0),
                view, projection, glm::vec4(0, 0, windowSize.x, windowSize.y));
            glm::vec3 rayMouse =
                glm::normalize(worldPos - mainSceneCamera.Position);

            auto line = Line(mainSceneCamera.Position, worldPos);
            auto line2 = Line(worldPos, cloudQuadObj.GetTransform()->position);
            line.setMVP(projection * view);
            line.draw();
            line2.setMVP(projection * view);
            line2.draw();

            // PianoCore::Log::Info(std::format("Raycast to mouse: {0}, {1},
            // {2}", rayMouse.x, rayMouse.y, rayMouse.z));

            debugUi.endFrame();
            pianoApp->GetRenderer()->Present();
            pianoApp->GetInput()->EndFrame();

            auto frameEnd = std::chrono::steady_clock::now();
            frameTimeMs =
                std::chrono::duration<float>(frameEnd - frameStart).count() *
                1000;

            auto targetFrameTimeMs = pianoApp->GetApplicationState()
                                         ->framerateTimer.GetTickSizeSeconds();
            if (frameTimeMs < targetFrameTimeMs) {
                float sleepTimeMs = targetFrameTimeMs - frameTimeMs;
                std::this_thread::sleep_for(
                    std::chrono::duration<float, milli>(sleepTimeMs));
            }

#pragma endregion Rendering Logic
        }
    }
};

int main() {
    PianoApp app;
    app.run();
}