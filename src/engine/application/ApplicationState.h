#pragma once
#include <engine/IWindow.h>
#include <engine/core/pointer.h>
#include <engine/debug/DebugState.h>

#include <memory>

namespace PianoCore {
struct ApplicationState {
    Debug::DebugState debugState;
    Ptr<Engine::IWindow> mainWindow;
};
}  // namespace PianoCore
