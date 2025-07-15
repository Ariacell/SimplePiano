#pragma once
#include "IWindow.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>

class PianoGLFWWindow : public Engine::IWindow
{
private:
    GLFWwindow *window = nullptr;

public:
    ~PianoGLFWWindow()
    {
        if (window)
        {
            glfwDestroyWindow(window);
        }
        glfwTerminate();
    }

    void Create(int width, int height, const char *title) override
    {
        int major, minor, rev;
        glfwGetVersion(&major, &minor, &rev);

        printf("GLFW version: %d.%d.%d\n", major, minor, rev);
        if (!glfwInit())
        {
            const char *description;
            glfwGetError(&description);
            fprintf(stderr, "GLFW Error: %s\n", description);
            throw std::runtime_error("Failed to init GLFW");
        }
        GLFWwindow *window = glfwCreateWindow(width, height, "SimplePiano", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwSetWindowSizeLimits(window, 200, 200, GLFW_DONT_CARE, GLFW_DONT_CARE);

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
        std::cout << "Loaded GLAD" << std::endl;
        this->window = window;
    }

    void PollEvents() override
    {
        glfwPollEvents();
    }

    void GetFrameBufferSize() override
    {
        glfwPollEvents();
    }

    bool ShouldClose() const override
    {
        return glfwWindowShouldClose(window);
    }

    void SetKeyCallback(GLFWkeyfun callback) override
    {
        glfwSetKeyCallback(window, callback);
    }

    void SwapBuffers() override
    {
        glfwSwapBuffers(window);
    }

    Engine::GLProcAddress GetWindowProcAddress() override
    {
        return (Engine::GLProcAddress)glfwGetProcAddress;
    }

    void *GetNativeHandle() override
    {
        return window;
    }
};
