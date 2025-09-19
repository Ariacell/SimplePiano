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
    this->appState.debugState = Debug::DebugState();
}

const ApplicationState* Application::GetApplicationState() {
    return &appState;
}

Application::~Application() {
    Log::Info("Destroying underlying PianoCore application class");
}
}  // namespace PianoCore
