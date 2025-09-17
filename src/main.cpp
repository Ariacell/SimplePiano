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

#include <filesystem>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "engine/graphics/VertexArray.h"
#include "engine/input/InputManager.h"
#include "game/components/GameObject.h"
#include "game/components/Model.h"
#include "game/components/ModelComponent.h"
#include <game/components/Mesh.h>

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
        std::shared_ptr<Shaders::IShader> openGlShader =
            std::make_shared<Shaders::OpenGlShader>("something", "something");

        std::cout << "Starting main application loop\n" << std::endl;

        Util::Timer appStateTimer;
        float appStateTickRateMs = 31.25f;
        appStateTimer.Init(appStateTickRateMs);

        Util::Timer frameRateTimer;
        float targetFramerate = 70.0f;
        float targetFrameTimeMs = (1 / targetFramerate) * 1000;
        frameRateTimer.Init(targetFrameTimeMs);

#pragma region Temporary setup for scene geometry, to remove once Scene abstraction is ready
        Shapes shapes;

        // Set up rectangle buffers
        auto triangle = shapes.getSampleRectangleData();
        auto cube = shapes.getSampleCubeVerts();

        Renderer::VertexArray va;
        Renderer::VertexBufferData rectVbData;
        rectVbData.data = (const void*)(triangle.first.data());
        rectVbData.size = (unsigned int)(sizeof(float) * triangle.first.size());

        Renderer::IndexBufferData rectIbData;
        rectIbData.data = triangle.second.data();
        rectIbData.count = triangle.second.size();

        Renderer::VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);

        Component::GameObject cloudObj;
        std::shared_ptr<Component::Mesh1> rectMesh(
            new Component::Mesh1(&va, rectVbData, rectIbData, layout));
        std::shared_ptr<Component::Material> cloudMat(
            new Component::Material(openGlShader, "path"));

        auto cloudQuadModel = cloudObj.AddComponent<Component::ModelComponent>(
            rectMesh, cloudMat);

        Component::Model ourModel("models/backpack/backpack.obj");
        Component::Model cubeOpenGlModel(Component::MeshType::Cube);

        Renderer::VertexArray cubeVa;
        Renderer::VertexBufferData cubeVbData;
        const unsigned int cubeIndices[6 * 6] = {
            // front and back

            0, 1, 3, 3, 1, 2, 1, 5, 2, 2, 5, 6, 5, 4, 6, 6, 4, 7,
            4, 0, 7, 7, 0, 3, 3, 2, 7, 7, 2, 6, 4, 5, 0, 0, 5, 1};
        cubeVbData.data = (const void*)(cube.data());
        cubeVbData.size = (unsigned int)(sizeof(float) * cube.size());

        Renderer::IndexBufferData cubeIbData;
        cubeIbData.data = cubeIndices;
        cubeIbData.count = 36;

        Renderer::VertexBufferLayout cubeLayout;
        cubeLayout.Push<float>(3);
        cubeLayout.Push<float>(2);
        Component::GameObject cubeObj;
        std::shared_ptr<Component::Mesh1> cubeMesh(
            new Component::Mesh1(&cubeVa, cubeVbData, cubeIbData, cubeLayout));
        std::shared_ptr<Component::Material> cubeMat(
            new Component::Material(openGlShader, "path"));
        auto cubeModel =
            cubeObj.AddComponent<Component::ModelComponent>(cubeMesh, cubeMat);
#pragma endregion

        float frameTimeMs = 0.0f;

        while (!window->ShouldClose()) {
            auto frameStart = std::chrono::steady_clock::now();
            window->PollEvents();

            appStateTimer.Update();
            frameRateTimer.Update();
            priorAppState = appState;

            appStateTimer.TickTimer(
                [&]() {
                    // blah
                    //  Do physics/app state things
                    // std::cout << "Application Ticks so far: "
                    //           << appStateTimer.GetTickCount() << std::endl;
                },
                5);

            // This probably doesn't need to be on a timer? Just want it to be
            // smooth but not sure if the 3rd person camera should be in app or
            // renderer yet
            frameRateTimer.TickTimer(
                [&]() {
                    mainSceneCamera.ProcessInput(inputManager.GetInputState(),
                                                 frameRateTimer.GetTickSize());
                    // std::cout << "Framerate time Ticks so far: "
                    //           << frameRateTimer.GetTickCount() << std::endl;
                },
                5);

#pragma region Rendering Logic
            debugUi.beginFrame();

            if (inputManager.isDebugWindowVisible()) {
                debugUi.renderDebugWindow(glfwWindow, debugWindowData,
                                          &appState, &inputManager);
            }

            renderer->SetWireframeRendering(
                debugWindowData->isWireframeRenderingEnabled);

            renderer->ClearScreen(0.1f, 0.1f, 0.1f, 1.0f);

            auto current_window_size = window.get()->GetWindowSize();

            glm::mat4 model = glm::mat4(1.0f);
            // model =
            //     glm::rotate(model, (float)glfwGetTime() *
            //     glm::radians(50.0f),
            // glm::vec3(0.5f, 1.0f, 0.0f));
            model = glm::rotate(model, 0.0f, glm::vec3(0.5f, 1.0f, 0.0f));
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
            unsigned int modelLoc =
                glGetUniformLocation(openGlShader.get()->GetID(), "model");
            unsigned int viewLoc =
                glGetUniformLocation(openGlShader.get()->GetID(), "view");
            unsigned int projLoc =
                glGetUniformLocation(openGlShader.get()->GetID(), "projection");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

            // ourModel.Draw(openGlShader);
            cubeOpenGlModel.Draw(openGlShader);
            renderer->DrawObject(&cloudObj);
            // Cube broken due to vertex order but doesn't really matter, just a
            // counting issue the mechanics of reading in different objects are
            // working! renderer->DrawObject(&cubeObj);

            debugUi.endFrame();
            renderer->Present();
            inputManager.EndFrame();

            auto frameEnd = std::chrono::steady_clock::now();
            frameTimeMs =
                std::chrono::duration<float>(frameEnd - frameStart).count() *
                1000;

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