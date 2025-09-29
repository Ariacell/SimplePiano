#pragma once

#include <engine/application/ApplicationState.h>
#include <engine/audio/audio.h>
#include <engine/input/InputManager.h>

namespace PianoCore {

class Application {
public:
    static Ptr<Application> Create();
    ~Application();

    void Start();
    void UpdateToFrame();

    ApplicationState* GetApplicationState();
    Input::InputManager* GetInput();
    Audio::AudioManager* GetAudio();

private:
    Application() = default;

    ApplicationState appState;
    Ptr<Input::InputManager> inputManager;
    Ptr<Audio::AudioManager> audioManager;
};
}  // namespace PianoCore
