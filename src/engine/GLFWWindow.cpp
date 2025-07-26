#include "GLFWWindow.h"

void PianoGLFWWindow::PianoGLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // Retrieve the instance associated with this window
    PianoGLFWWindow *instance = static_cast<PianoGLFWWindow *>(glfwGetWindowUserPointer(window));
    if (instance && instance->keyCallback_)
    {
        instance->keyCallback_(key, action, mods);
    }
}

PianoGLFWWindow::PianoGLFWWindow()
{
    // Noop constructor, prefer the CREATE for more precise control over the window lifecycle
}

PianoGLFWWindow::~PianoGLFWWindow()
{
    if (window)
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void PianoGLFWWindow::Create(int width, int height, const char *title)
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
    glfwSetWindowUserPointer(window, reinterpret_cast<void *>(this));

    glfwSetKeyCallback(window, PianoGLFWKeyCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    std::cout << "Loaded GLAD" << std::endl;
    this->window = window;
}

void PianoGLFWWindow::PollEvents()
{
    glfwPollEvents();
}

void PianoGLFWWindow::GetFrameBufferSize()
{
    glfwPollEvents();
}

bool PianoGLFWWindow::ShouldClose() const
{
    return glfwWindowShouldClose(window);
}

void PianoGLFWWindow::SetKeyCallback(std::function<void(int, int, int)> callback)
{
    keyCallback_ = callback;
}

void PianoGLFWWindow::SwapBuffers()
{
    glfwSwapBuffers(window);
}

Engine::GLProcAddress PianoGLFWWindow::GetWindowProcAddress()
{
    return (Engine::GLProcAddress)glfwGetProcAddress;
}

void *PianoGLFWWindow::GetNativeHandle()
{
    return window;
}
