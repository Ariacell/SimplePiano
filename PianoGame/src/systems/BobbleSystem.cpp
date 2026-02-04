#include "BobbleSystem.h"
#include <iostream>
#include <ecs/World.h>
#include <components/Transform.h>
#include <chrono>
#include "../components/Rigidbody.h"
#include <glm/vec3.hpp>

extern World gWorld;

// Little toy system to make everything bobble at 0 height
void BobbleSystem::Update(float dt)
{
    std::cout << "Updating Bobble System" << std::endl;

	for (auto const& entity : mEntities)
	{
        // std::cout << "Updating entity" << entity << "\n" << std::endl;
		auto& transform = gWorld.GetComponent<Component::Transform>(entity);
		auto& body = gWorld.GetComponent<RigidBody>(entity);
        auto currentTime = std::chrono::system_clock::now().time_since_epoch();
        // transform.rotate(glm::quat(1.0f,1.0f,1.0f, 0.0f) * dt * 0.0f);
        // transform.translate(glm::vec3(100.0f,0.0f,0.0f));
        if (transform.position.y < 0.0f){
            body.velocity = (glm::vec3(0.0f,.1f,0.0f));
        } else {
            body.velocity = (glm::vec3(0.0f,-.1f,0.0f));
        }
        // transform.position += glm::vec3((float)glm::sin(currentTime.count()));
    }

}
