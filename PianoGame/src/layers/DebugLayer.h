#pragma once

#include <application/IAppLayer.h>
#include <debug/debugUI.h>
#include <input/InputManager.h>

#include <vector>

#include <application/Application.h>

namespace PianoApp {

class PianoAppDebugLayer : public PianoCore::IAppLayer {
public:
    PianoAppDebugLayer(PerspectiveCamera &cameraToFollow,
                       PianoCore::Application &parentApplication);
    void Init() override;
    void Update(Input::InputManager &input) override;
    void Render() override;
    void Suspend() override;

private:
    Ptr<PianoCore::DebugUi> debugUi;
    bool m_isLayerVisible = false;
};
}  // namespace PianoApp