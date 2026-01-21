#pragma once
#include "../IWindow.h"
#include "../core/pointer.h"
#include "../debug/DebugState.h"
#include "../util/timer.h"

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
