#include "Application.h"
#define GLFW_INCLUDE_NONE
#include <engine/GLFWWindow.h>
#include <engine/RendererFactory.h>
#include <engine/application/ApplicationConstants.h>
#include <engine/core/log.h>

#include <memory>

namespace PianoCore {

Ptr<Application> Application::Create() {
    auto app = std::unique_ptr<Application>(new Application());

    app->appState.mainWindow = std::make_unique<PianoGLFWWindow>();
    app->appState.mainWindow->Create(PianoCore::WINDOW_DEFAULTS::WINDOW_WIDTH,
                                     PianoCore::WINDOW_DEFAULTS::WINDOW_HEIGHT,
                                     "SimplePiano");
    Log::Info("Finished Init PianoCore Application Window");
    app->appState.debugState = Debug::DebugState();

    app->appState.simulationTimer = Util::Timer(
        PianoCore::APPLICATION_DEFAULTS::TARGET_SIMULATION_TICKS_PER_SECOND);
    app->appState.framerateTimer =
        Util::Timer(PianoCore::APPLICATION_DEFAULTS::TARGET_FRAMES_PER_SECOND);

    app->inputManager =
        std::make_unique<Input::InputManager>(*app->appState.mainWindow);

    app->audioManager = std::make_unique<Audio::AudioManager>();

    app->renderer = RendererFactory::CreateRenderer(RendererType::OpenGL);

    app->debugUI = std::make_unique<DebugUiLayer>();

    return app;
}

ApplicationState* Application::GetApplicationState() {
    return &appState;
}

Input::InputManager* Application::GetInput() {
    return inputManager.get();
}

Audio::AudioManager* Application::GetAudio() {
    return audioManager.get();
}

Engine::IRenderer* Application::GetRenderer() {
    return renderer.get();
}

Application::~Application() {
    Log::Info("Destroying underlying PianoCore application class");
}

void Application::Start() {
    std::cout << "Starting main application loop\n" << std::endl;

    appState.simulationTimer.Init();
    appState.framerateTimer.Init();

    renderer->Initialize(*appState.mainWindow);

    // TODO: SP #6 This shouldn't be necessary. Very smelly and probably means
    // I've fuckyduckied my interface somewhat.
    GLFWwindow* glfwWindow =
        static_cast<GLFWwindow*>(appState.mainWindow->GetNativeHandle());

    // TODO: SP #7 Why is appState responsible for some of the startup info for
    // this layer?
    debugUI->init(glfwWindow, &appState.debugState.mainDebugWindowData,
                  nullptr);
    inputManager->bindDebugSettings(&appState.debugState.mainDebugWindowData);
    std::cout << ("Finished Init Input and DebugUi\n");
}

void Application::UpdateToFrame() {
    // Update the underlying application state to the current frame as
    // appropriate
    appState.simulationTimer.Update();
    appState.framerateTimer.Update();

    GLFWwindow* glfwWindow =
        static_cast<GLFWwindow*>(appState.mainWindow->GetNativeHandle());
    debugUI->beginFrame();

    if (inputManager->isDebugWindowVisible()) {
        debugUI->renderDebugWindow(glfwWindow,
                                   &appState.debugState.mainDebugWindowData,
                                   &appState, inputManager.get());
    }

    renderer->SetWireframeRendering(
        appState.debugState.mainDebugWindowData.isWireframeRenderingEnabled);
    // Note: While SP #7 is in play this call being here is causing the debug
    // windows to render behind the rest of the scene geometry. Should be fixed
    // once the rendering loop is properly extracted into application loop
    // callbacks.
    debugUI->endFrame();
}
}  // namespace PianoCore
