#include "PhysicsSystem.h"
#include <iostream>
#include <ecs/World.h>
#include <components/Transform.h>
#include <chrono>
#include "../components/Rigidbody.h"
#include <glm/vec3.hpp>

extern World gWorld;

// Little toy system to make everything bobble at 0 height
void PhysicsSystem::Update(float dt)
{
    std::cout << "Updating Bobble System" << std::endl;

	for (auto const& entity : mEntities)
	{
        // std::cout << "Updating entity" << entity << "\n" << std::endl;
		auto& transform = gWorld.GetComponent<Component::Transform>(entity);
		auto& body = gWorld.GetComponent<RigidBody>(entity);
        body.velocity += body.acceleration;
        transform.position += body.velocity;
    }

}
