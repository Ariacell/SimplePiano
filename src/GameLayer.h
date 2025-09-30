#pragma once
#include <engine/application/Application.h>
#include <engine/application/IAppLayer.h>

namespace PianoApp {

struct PianoAppGameData {};

class PianoAppGameLayer : public PianoCore::IAppLayer {
public:
    PianoAppGameLayer();
    void SimulationMove() override;
    void FrameMove() override;

private:
    PianoAppGameData gameDate;
};

}  // namespace PianoApp
