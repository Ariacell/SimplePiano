#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>

#include "IWindow.h"

class PianoGLFWWindow : public Engine::IWindow {
private:
    GLFWwindow *window = nullptr;

    static void PianoGLFWKeyCallback(GLFWwindow *window, int key, int scancode,
                                     int action, int mods);
    static void PianoGLFWMouseButtonCallback(GLFWwindow *window, int key,
                                             int action, int mods);
    static void PianoGLFWCursorPositionCallback(GLFWwindow *window, double xpos,
                                                double ypos);
    std::function<void(int, int, int)> keyCallback_ = 0;
    std::function<void(int, int, int)> mouseButtonCallback_ = 0;
    std::function<void(double, double)> cursorPosCallback_ = 0;

public:
    PianoGLFWWindow();
    ~PianoGLFWWindow() override;
    void Create(int width, int height, const char *title) override;
    void SetKeyCallback(
        std::function<void(int key, int action, int mods)> callback) override;
    void SetCursorPosCallback(
        std::function<void(double xpos, double ypos)> callback) override;
    void PollEvents() override;
    bool ShouldClose() const override;
    void SwapBuffers() override;
    void GetFrameBufferSize(int &frameWidth, int &frameHeight) override;
    glm::vec2 GetWindowSize() override;

    Engine::GLProcAddress GetWindowProcAddress() override;
    void *GetNativeHandle() override;  // platform-specific pointer
};
