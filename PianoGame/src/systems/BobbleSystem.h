#pragma once

#include <ecs/System.h>

class BobbleSystem : public System {
    public:
        BobbleSystem() {};
        void Update(float dt) override;
};