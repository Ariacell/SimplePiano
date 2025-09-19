#pragma once
#include <engine/application/ApplicationState.h>

namespace PianoCore {

class Application {
public:
    Application();
    ~Application();

    const ApplicationState* GetApplicationState();

private:
    ApplicationState appState;
};
}  // namespace PianoCore
