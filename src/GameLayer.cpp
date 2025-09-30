
#include <GameLayer.h>
#include <engine/application/IAppLayer.h>
#include <engine/core/log.h>

namespace PianoApp {

PianoAppGameLayer::PianoAppGameLayer() {
    PianoCore::Log::Info("Constructing PianoAppGameLayer");
}

void PianoAppGameLayer::SimulationMove() {
    PianoCore::Log::Info("Simulation Moving PianoAppGameLayer");
}
void PianoAppGameLayer::FrameMove() {
    PianoCore::Log::Info("Frame Moving PianoAppGameLayer");
}
}  // namespace PianoApp
