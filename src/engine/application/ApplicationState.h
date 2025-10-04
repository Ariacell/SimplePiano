#pragma once
#include <engine/IWindow.h>
#include <engine/core/pointer.h>
#include <engine/debug/DebugState.h>
#include <util/timer.h>

#include <memory>

namespace PianoCore {
class ApplicationState {
public:
    Debug::DebugState debugState;
    Ptr<Engine::IWindow> mainWindow;
    Util::Timer framerateTimer;

    ApplicationState() = default;
};
}  // namespace PianoCore
