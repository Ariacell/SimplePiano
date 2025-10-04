#include "Application.h"
#define GLFW_INCLUDE_NONE
#include <engine/GLFWWindow.h>
#include <engine/RendererFactory.h>
#include <engine/application/ApplicationConstants.h>
#include <engine/core/log.h>
#include <engine/input/InputKeys.h>

#include <memory>
#include <thread>

namespace PianoCore {

Ptr<Application> Application::Create() {
    auto app = std::unique_ptr<Application>(new Application());

    app->m_AppState.mainWindow = std::make_unique<PianoGLFWWindow>();
    app->m_AppState.mainWindow->Create(
        PianoCore::WINDOW_DEFAULTS::WINDOW_WIDTH,
        PianoCore::WINDOW_DEFAULTS::WINDOW_HEIGHT, "SimplePiano");
    Log::Info("Finished Init PianoCore Application Window");
    app->m_AppState.debugState = Debug::DebugState();

    app->m_AppState.framerateTimer =
        Util::Timer(PianoCore::APPLICATION_DEFAULTS::TARGET_FRAMES_PER_SECOND);

    app->inputManager =
        std::make_unique<Input::InputManager>(*app->m_AppState.mainWindow);

    app->audioManager = std::make_unique<Audio::AudioManager>();

    app->m_ApplicationRenderer =
        RendererFactory::CreateRenderer(RendererType::OpenGL);
    app->m_ApplicationRenderer->Initialize(*app->m_AppState.mainWindow.get());

    return app;
}

ApplicationState* Application::GetApplicationState() {
    return &m_AppState;
}

Input::InputManager* Application::GetInput() {
    return inputManager.get();
}

Audio::AudioManager* Application::GetAudio() {
    return audioManager.get();
}

Engine::IRenderer* Application::GetRenderer() {
    return m_ApplicationRenderer.get();
}

Application::~Application() {
    Log::Info("Destroying underlying PianoCore application class");
}

void Application::Start() {
    std::cout << "Starting main application loop\n" << std::endl;

    m_AppState.framerateTimer.Init();

    for (auto& layer : m_AppLayers) {
        layer->Init();
    };
    while (!m_AppState.mainWindow->ShouldClose()) {
        UpdateToFrame();
    }
}

void Application::UpdateToFrame() {
    auto frameStart = std::chrono::steady_clock::now();
    m_AppState.mainWindow->PollEvents();

    if (inputManager->GetInputState().WasKeyPressed(Input::APP_KEY_ESCAPE)) {
        m_AppState.mainWindow->SignalShouldClose();
    }

    m_AppState.framerateTimer.Update();

    // Update layers based on application observed inputs TODO: add time back
    // into this as an optional observable for each layer to di the time
    for (auto& layer : m_AppLayers) {
        layer->Update(*inputManager);
    };

    // Render all layers
    m_ApplicationRenderer->ClearScreen(0.1F, 0.1F, 0.1F, 1.0F);
    m_ApplicationRenderer->SetWireframeRendering(
        m_AppState.debugState.mainDebugWindowData.isWireframeRenderingEnabled);
    for (auto& layer : m_AppLayers) {
        layer->Render();
    };
    m_ApplicationRenderer->Present();

    inputManager->EndFrame();

    CapFrameRate(frameStart, m_AppState.framerateTimer.GetTickSizeSeconds());
}

void Application::CapFrameRate(
    std::chrono::_V2::steady_clock::time_point frameStartTime,
    float targetFrameTimeMs) {
    auto frameEnd = std::chrono::steady_clock::now();
    float frameTimeMs =
        std::chrono::duration<float>(frameEnd - frameStartTime).count() * 1000;

    if (frameTimeMs < targetFrameTimeMs) {
        float sleepTimeMs = targetFrameTimeMs - frameTimeMs;
        std::this_thread::sleep_for(
            std::chrono::duration<float, milli>(sleepTimeMs));
    }
}
}  // namespace PianoCore
