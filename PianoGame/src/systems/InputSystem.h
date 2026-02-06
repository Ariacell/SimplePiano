#pragma once

#define GLFW_INCLUDE_NONE
#include <ecs/System.h>
#include <physics/Ray.h>
#include <physics/Raycasting.h>
#include <input/InputManager.h>
#include <input/InputKeys.h>
#include <application/Application.h>
#include <components/BoundingBoxComponent.h>
#include <components/SelectableComponent.h>

class InputSystem : public System {
    public:
        InputSystem(
            const Input::InputManager& _input, 
            const PerspectiveCamera& camera,
            PianoCore::Application& parentApp) : 
            mInputManager(_input),
            mCamera(camera),
            mApp(parentApp)
            {};
        void Update(float dt) override;
    private:
        const Input::InputManager& mInputManager;
        const PerspectiveCamera& mCamera;
        PianoCore::Application& mApp;
};