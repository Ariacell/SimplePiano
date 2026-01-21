#pragma once
#include <functional>
#include <glm/vec2.hpp>

namespace Engine {
using GLProcAddress = void *(*)(const char *);
class IWindow {
public:
    virtual ~IWindow() = default;

    virtual void Create(int width, int height, const char *title) = 0;
    virtual void SetKeyCallback(
        std::function<void(int key, int action, int mods)> callback) = 0;
    virtual void SetCursorPosCallback(
        std::function<void(double xpos, double ypos)> callback) = 0;
    virtual void PollEvents() = 0;
    virtual bool ShouldClose() const = 0;
    virtual void SignalShouldClose() = 0;
    virtual void SwapBuffers() = 0;
    const virtual void GetFrameBufferSize(int &frameWidth,
                                          int &frameHeight) = 0;
    const virtual glm::vec2 GetWindowSize() = 0;

    virtual const GLProcAddress GetWindowProcAddress() = 0;
    virtual void *GetNativeHandle() = 0;  // platform-specific pointer
};
}  // namespace Engine