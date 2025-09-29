#include "Application.h"

#include <engine/GLFWWindow.h>
#include <engine/application/ApplicationConstants.h>
#include <engine/core/log.h>

#include <memory>

namespace PianoCore {

Application::Application() {
    // Todo: figure out if this is really the cleanest way to create this
    // window class...
    appState.mainWindow = std::make_unique<PianoGLFWWindow>();
    appState.mainWindow->Create(PianoCore::WINDOW_DEFAULTS::WINDOW_WIDTH,
                                PianoCore::WINDOW_DEFAULTS::WINDOW_HEIGHT,
                                "SimplePiano");
    Log::Info("Finished Init PianoCore Application Window");
    appState.debugState = Debug::DebugState();

    appState.simulationTimer = Util::Timer(
        PianoCore::APPLICATION_DEFAULTS::TARGET_SIMULATION_TICKS_PER_SECOND);
    appState.framerateTimer =
        Util::Timer(PianoCore::APPLICATION_DEFAULTS::TARGET_FRAMES_PER_SECOND);
}

ApplicationState* Application::GetApplicationState() {
    return &appState;
}

Application::~Application() {
    Log::Info("Destroying underlying PianoCore application class");
}

void Application::Start() {
    appState.simulationTimer.Init();
    appState.framerateTimer.Init();
}

void Application::UpdateToFrame() {
    // Update the underlying application state to the current frame as
    // appropriate
    appState.simulationTimer.Update();
    appState.framerateTimer.Update();
}
}  // namespace PianoCore
