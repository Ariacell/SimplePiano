#pragma once
#define GLFW_INCLUDE_NONE

#include <application/Application.h>
#include <application/IAppLayer.h>
#include <ecs/World.h>
#include <input/InputManager.h>
#include <shaders/OpenGlShader.h>
#include <util/timer.h>
#include <RenderSystem.h>
#include <BobbleSystem.h>
#include <PhysicsSystem.h>

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
    std::shared_ptr<RenderSystem> mRenderSystem;
    std::shared_ptr<BobbleSystem> mBobbleSystem;
    std::shared_ptr<PhysicsSystem> mPhysicsSystem;

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
