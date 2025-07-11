#pragma once

#include <GLFW/glfw3.h>

class DebugUiLayer {
public:
    void init(GLFWwindow* window);
    void beginFrame();
    void endFrame();
    void shutdown();

    void renderDebugWindow(bool show);
};