#pragma once

#include "../core/log.h"
#include "../input/InputManager.h"

namespace PianoCore {
class IAppLayer {
public:
    virtual ~IAppLayer() = default;

    virtual void Init() = 0;
    virtual void Update(Input::InputManager &input) = 0;
    virtual void Render() = 0;
    virtual void Suspend() = 0;

private:
    unsigned int m_LayerId;
    unsigned int m_IsSuspended;
};
}  // namespace PianoCore