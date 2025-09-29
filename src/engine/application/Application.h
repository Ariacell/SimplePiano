#pragma once
#include <engine/application/ApplicationState.h>

namespace PianoCore {

class Application {
public:
    Application();
    ~Application();

    void Start();
    void UpdateToFrame();

    ApplicationState* GetApplicationState();

private:
    ApplicationState appState;
};
}  // namespace PianoCore
