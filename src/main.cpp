#define GLFW_INCLUDE_NONE
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <audio/audio.h>
#include <input/input.h>
#include <ui/debugUI.h>
#include <imgui.h>

Input::InputManager inputManager;

static void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods); // forward to ImGui
    inputManager.keyCallback(key, action);
}

class PianoApp
{
public:
    Audio::AudioManager audioManager;
    DebugUiLayer debugUi;

    void run()
    {
        auto *window = initWindow();
        std::cout << ("Finished Init Window\n");
        audioManager.initAudio();
        std::cout << ("Finished Init Audio\n");
        debugUi.init(window);
        std::cout << ("Finished Init DebugUi\n");

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            debugUi.beginFrame();
            ImGui::ShowDemoWindow();

            // Draw debug window if enabled
            if (inputManager.isDebugWindowVisible())
            {
                std::cout<<("Debug window should be visible!\n");
                debugUi.renderDebugWindow(inputManager.isDebugWindowVisible());
            }
            
            // Rendering
            // ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            debugUi.endFrame();
            glfwSwapBuffers(window);
        }
    }

private:
    GLFWwindow *initWindow()
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
        GLFWwindow *window = glfwCreateWindow(1280, 720, "SimplePiano", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent( window );

        // Set input callbacks
        glfwSetKeyCallback(window, glfwKeyCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }

        return window;
    }
};

int main()
{
    PianoApp app;

    app.run();
    // std::cout<<("Hello World");
}