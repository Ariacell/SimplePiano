#ifndef APPSTATE_H
#define APPSTATE_H
#include <engine/IWindow.h>
#include <engine/debug/DebugState.h>

namespace State {
struct ApplicationState {
    Debug::DebugState debugState;
    Engine::IWindow *mainWindow;
};
}  // namespace State

#endif