#pragma once

#include "IRenderer.h"
#include "ApplicationState.h"
#include "IAppLayer.h"
#include "audio/audio.h"
#include "debug/debugUI.h"
#include "input/InputManager.h"

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
    Engine::IRenderer* GetRenderer();

    template <typename T,
              typename std::enable_if<std::is_base_of<IAppLayer, T>::value,
                                      int>::type = 0>
    void PushLayer(std::shared_ptr<T> layerInstance) {
        m_AppLayers.push_back(
            std::static_pointer_cast<IAppLayer>(layerInstance));
    }

private:
    Application() = default;

    void CapFrameRate(std::chrono::_V2::steady_clock::time_point frameStartTime,
                      float targetFrameTimeMs);

    std::vector<Ref<IAppLayer>> m_AppLayers = {};

    ApplicationState m_AppState;
    Ptr<Engine::IRenderer> m_ApplicationRenderer;
    Ptr<Input::InputManager> inputManager;
    Ptr<Audio::AudioManager> audioManager;
};
}  // namespace PianoCore
