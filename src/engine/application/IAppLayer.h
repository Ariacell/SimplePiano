#pragma once

#include <engine/core/log.h>

namespace PianoCore {
class IAppLayer {
public:
    virtual ~IAppLayer() = default;

    virtual void SimulationMove() = 0;
    virtual void FrameMove() = 0;

private:
    unsigned int m_LayerId;
};
}  // namespace PianoCore