#ifndef CAMERA_H
#define CAMERA_H

#include <engine/input/InputState.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

class PerspectiveCamera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Note Front Up and Right are maintained alongside Orientation for easy of
    // access, bit redundant technically to have both, I might remove this later
    glm::mat4 Orientation = glm::mat4(1.0f);

    // I also want the option to lock pitch/roll sometimes because doing
    // backflips hurts my brain
    bool isRollLocked = false;
    bool isPitchConstrained = false;
    float Pitch = 0.0f;
    float MaxPitch = glm::radians(89.0f);

    float MovementSpeed;
    float RollSpeed;
    float MouseSensitivity;
    float Zoom;

    PerspectiveCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
                      glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    ~PerspectiveCamera() {
        std::cout << "Destroying PerspetiveCamera" << std::endl;
    }

    glm::mat4 GetViewMatrix();
    void ProcessInput(Input::InputState inputState, float deltaTime);

private:
    void ProcessPitchYawRoll(Input::InputState inputState, float deltaTime,
                             bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void ApplyRoll(float deltaRoll);
    void updateCameraVectors();
};

#endif
