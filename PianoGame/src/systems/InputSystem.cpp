#include <iostream>
#include <ecs/World.h>
#include <components/Transform.h>
#include <chrono>
#include "../components/Rigidbody.h"
#include <glm/vec3.hpp>
#include "InputSystem.h"


extern World gWorld;

void InputSystem::Update(float dt)
{
      if (mInputManager.GetInputState().WasKeyPressed(Input::APP_KEY_MOUSE_1)) {
        glm::vec2 windowSize = mApp.GetApplicationState()
                                    ->mainWindow->GetWindowSize();
            glm::mat4 projection = glm::perspective(
                glm::radians(45.0F), (float)windowSize.x / (float)windowSize.y,
                0.1F, 100.0F);
            glm::vec3 worldPos = glm::unProject(
                glm::vec3(mInputManager.GetMousePosition().x,
                        windowSize.y - mInputManager.GetMousePosition().y, 0.0),
                mCamera.GetViewMatrix(), projection,
                glm::vec4(0, 0, windowSize.x, windowSize.y));
            glm::vec3 rayMouse = glm::normalize(worldPos - mCamera.Position);

            float hitDistance = 0.0F;
            PianoPhysics::Ray ray(mCamera.Position, rayMouse);
            for (auto const& entity : mEntities) {
                auto const& transform = gWorld.GetComponent<Component::Transform>(entity);
		        auto& selectable = gWorld.GetComponent<Component::SelectableComponent>(entity);
		        auto& bbox = gWorld.GetComponent<Component::BoundingBoxComponent>(entity);
                
                bbox.DrawDebug(projection, mCamera.GetViewMatrix());

                if (PianoPhysics::CheckRayToAABBIntersection(
                    ray,
                    bbox.GetMinExtents() + transform.position,
                    bbox.GetMaxExtents() + transform.position,
                    hitDistance)) {
                PianoCore::Log::Info("INTERSECTION at depth %4.2f", hitDistance);
                selectable.SetSelected(true);
                } else {
                    selectable.SetSelected(false);
            }
        }
    }
}