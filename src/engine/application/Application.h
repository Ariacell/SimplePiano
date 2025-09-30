#pragma once

#include <engine/IRenderer.h>
#include <engine/application/ApplicationState.h>
#include <engine/application/IAppLayer.h>
#include <engine/audio/audio.h>
#include <engine/debug/debugUI.h>
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

    std::vector<Ref<IAppLayer>> m_AppLayers = {};

    ApplicationState m_AppState;
    Ptr<DebugUiLayer> debugUI;
    Ptr<Input::InputManager> inputManager;
    Ptr<Audio::AudioManager> audioManager;
    Ptr<Engine::IRenderer> renderer;
};
}  // namespace PianoCore
