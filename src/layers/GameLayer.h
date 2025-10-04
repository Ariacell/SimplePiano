#pragma once
#define GLFW_INCLUDE_NONE

#include <engine/application/Application.h>
#include <engine/application/IAppLayer.h>
#include <engine/input/InputManager.h>
#include <engine/shaders/OpenGlShader.h>
#include <util/timer.h>

namespace PianoApp {

struct PianoAppGameData {};

class PianoAppGameLayer : public PianoCore::IAppLayer {
public:
    PianoAppGameLayer(PerspectiveCamera &mainGameCamera,
                      PianoCore::Application &parentApplication);
    ~PianoAppGameLayer();

    void Init() override;

    void Update(Input::InputManager &input) override;
    void Render() override;
    void Suspend() override;

private:
    PianoAppGameData gameData;
    Util::Timer simulationTimer;
    Engine::IRenderer &renderer;

    Component::GameObject cloudObj;
    Component::GameObject cloudQuadObj;
    std::shared_ptr<Shaders::IShader> openGlShader;

    PerspectiveCamera &mainCamera;
    PianoCore::Application &parentApplication;
};

}  // namespace PianoApp
