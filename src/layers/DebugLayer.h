#pragma once

#include <engine/application/IAppLayer.h>
#include <engine/debug/debugUI.h>
#include <engine/input/InputManager.h>

#include <vector>

#include "engine/application/Application.h"

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