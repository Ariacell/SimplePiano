#pragma once

#include <ecs/System.h>

class PhysicsSystem : public System {
    public:
        PhysicsSystem() {};
        void Update(float dt) override;
};