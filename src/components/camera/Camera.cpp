#include <components/camera/Camera.h>
#include <engine/input/InputKeys.h>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      MovementSpeed(2.5f),
      MouseSensitivity(0.1f),
      Zoom(45.0f)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    MovementSpeed = .2f;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessInput(Input::InputState inputState, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    glm::vec3 movementVector = glm::vec3(0,0,0);
    if (inputState.IsKeyDown(Input::APP_KEY_W))
        movementVector += Front;
    if (inputState.IsKeyDown(Input::APP_KEY_S))
        movementVector -= Front;
    if (inputState.IsKeyDown(Input::APP_KEY_A))
        movementVector -= Right;
    if (inputState.IsKeyDown(Input::APP_KEY_D))
        movementVector += Right;
    if(movementVector != glm::vec3(0,0,0))
        Position += glm::normalize(movementVector) * velocity;
    float x,y = .0f;
    inputState.GetMouseDelta(x,y);
    ProcessMouseMovement(x,y, true);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    Zoom -= yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
