#include <components/camera/Camera.h>
#include <engine/input/InputKeys.h>

Camera::Camera(glm::vec3 position, glm::vec3 up)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      MovementSpeed(2.5f),
      MouseSensitivity(0.001f),
      Zoom(45.0f) {
    Position = position;
    WorldUp = up;
    MovementSpeed = 1.0f;
    RollSpeed = .01f;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessInput(Input::InputState inputState, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    glm::vec3 movementVector = glm::vec3(0, 0, 0);
    if (inputState.IsKeyDown(Input::APP_KEY_W))
        movementVector += Front;
    if (inputState.IsKeyDown(Input::APP_KEY_S))
        movementVector -= Front;
    if (inputState.IsKeyDown(Input::APP_KEY_A))
        movementVector -= Right;
    if (inputState.IsKeyDown(Input::APP_KEY_D))
        movementVector += Right;
    if (inputState.IsKeyDown(Input::APP_KEY_SPACE))
        movementVector += Up;
    if (inputState.IsKeyDown(Input::APP_KEY_LCTRL))
        movementVector -= Up;
    if (movementVector != glm::vec3(0, 0, 0))
        Position += glm::normalize(movementVector) * velocity;
    ProcessPitchYawRoll(inputState, deltaTime, true);
}

void Camera::ProcessPitchYawRoll(Input::InputState inputState, float deltaTime,
                                 bool constrainPitch) {
    if (inputState.IsKeyDown(Input::APP_KEY_E))
        ApplyRoll(RollSpeed);
    if (inputState.IsKeyDown(Input::APP_KEY_Q))
        ApplyRoll(-RollSpeed);

    // Rotation if rotate keybind pressed
    if (inputState.IsKeyDown(Input::APP_KEY_MOUSE_2)) {
        float xoffset, yoffset = .0f;
        inputState.GetMouseDelta(xoffset, yoffset);
        xoffset *= -MouseSensitivity;
        yoffset *= MouseSensitivity;

        // glm::vec3 localUp = glm::vec3(Orientation[1]);
        // glm::vec3 localRight = glm::vec3(Orientation[0]);

        glm::mat4 yawRot = glm::rotate(glm::mat4(1.0f), xoffset, Up);
        glm::mat4 pitchRot = glm::rotate(glm::mat4(1.0f), yoffset, Right);

        Orientation = yawRot * pitchRot * Orientation;

        // if (constrainPitch) {
        //     if (Pitch > 89.0f)
        //         Pitch = 89.0f;
        //     if (Pitch < -89.0f)
        //         Pitch = -89.0f;
        // }
    }
    updateCameraVectors();
}

void Camera::ApplyRoll(float deltaRoll) {
    glm::mat4 rollRotation = glm::rotate(glm::mat4(1.0f), deltaRoll, Front);
    Orientation = rollRotation * Orientation;
}

void Camera::ProcessMouseScroll(float yoffset) {
    Zoom -= yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    Right = glm::normalize(glm::vec3(Orientation[0]));
    Up = glm::normalize(glm::vec3(Orientation[1]));
    Front = glm::normalize(-glm::vec3(Orientation[2]));
}
