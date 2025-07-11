#include <iostream>
#include <GLFW/glfw3.h>
#include <audio/audio.h>
#include <input/input.h>

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

    void run()
    {
        auto *window = initWindow();
        std::cout << ("Finished Init Window\n");
        audioManager.initAudio();
        std::cout << ("Finished Init Audio\n");

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            // Start ImGui frame
            // ImGui_ImplOpenGL3_NewFrame();
            // ImGui_ImplGlfw_NewFrame();
            // ImGui::NewFrame();

            // // Draw debug window if enabled
            // if (inputManager.isDebugWindowVisible())
            // {
            //     ImGui::Begin("Debug Window");
            //     ImGui::Text("F1 toggled this debug window.");
            //     ImGui::End();
            // }

            // Rendering
            // ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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

        // Set input callbacks

        glfwSetKeyCallback(window, glfwKeyCallback);
        return window;
    }
};

int main()
{
    PianoApp app;

    app.run();
    // std::cout<<("Hello World");
}