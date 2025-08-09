#define GLFW_INCLUDE_NONE
#include "GLFWWindow.h"

#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

#include "IWindow.h"

void PianoGLFWWindow::PianoGLFWKeyCallback(GLFWwindow *window, int key,
                                           int scancode, int action, int mods) {
    PianoGLFWWindow *instance =
        static_cast<PianoGLFWWindow *>(glfwGetWindowUserPointer(window));
    if (instance && instance->keyCallback_) {
        instance->keyCallback_(key, action, mods);
    }
}

void PianoGLFWWindow::PianoGLFWMouseButtonCallback(GLFWwindow *window, int key,
                                                   int action, int mods) {
    PianoGLFWWindow *instance =
        static_cast<PianoGLFWWindow *>(glfwGetWindowUserPointer(window));
    if (instance && instance->keyCallback_) {
        instance->keyCallback_(key, action, mods);
    }
}

void PianoGLFWWindow::PianoGLFWCursorPositionCallback(GLFWwindow *window,
                                                      double xPos,
                                                      double yPos) {
    PianoGLFWWindow *instance =
        static_cast<PianoGLFWWindow *>(glfwGetWindowUserPointer(window));
    if (instance && instance->cursorPosCallback_) {
        instance->cursorPosCallback_(xPos, yPos);
    }
}

PianoGLFWWindow::PianoGLFWWindow() {
    // Noop constructor, prefer the CREATE for more precise control over the
    // window lifecycle
}

PianoGLFWWindow::~PianoGLFWWindow() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void PianoGLFWWindow::Create(int width, int height, const char *title) {
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);

    printf("GLFW version: %d.%d.%d\n", major, minor, rev);
    if (!glfwInit()) {
        const char *description;
        glfwGetError(&description);
        fprintf(stderr, "GLFW Error: %s\n", description);
        throw std::runtime_error("Failed to init GLFW");
    }
    GLFWwindow *window =
        glfwCreateWindow(width, height, "SimplePiano", NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwSetWindowSizeLimits(window, 200, 200, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, reinterpret_cast<void *>(this));

    glfwSetKeyCallback(window, PianoGLFWKeyCallback);
    glfwSetMouseButtonCallback(window, PianoGLFWMouseButtonCallback);
    glfwSetCursorPosCallback(window, PianoGLFWCursorPositionCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    std::cout << "Loaded GLAD" << std::endl;
    this->window = window;
}

void PianoGLFWWindow::PollEvents() {
    glfwPollEvents();
}

void PianoGLFWWindow::GetFrameBufferSize() {
    glfwPollEvents();
}

glm::vec2 PianoGLFWWindow::GetWindowSize() {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return glm::vec2(width, height);
}

bool PianoGLFWWindow::ShouldClose() const {
    return glfwWindowShouldClose(window);
}

void PianoGLFWWindow::SetKeyCallback(
    std::function<void(int, int, int)> callback) {
    keyCallback_ = callback;
}

void PianoGLFWWindow::SetCursorPosCallback(
    std::function<void(double, double)> callback) {
    cursorPosCallback_ = callback;
}

void PianoGLFWWindow::SwapBuffers() {
    glfwSwapBuffers(window);
}

Engine::GLProcAddress PianoGLFWWindow::GetWindowProcAddress() {
    return (Engine::GLProcAddress)glfwGetProcAddress;
}

void *PianoGLFWWindow::GetNativeHandle() {
    return window;
}
