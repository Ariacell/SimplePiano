#define GLFW_INCLUDE_NONE
#include <engine/RendererFactory.h>
#include <engine/graphics/OpenGLLine.h>
#include <game/components/Mesh.h>
#include <layers/GameLayer.h>
#include <stb_image/stb_image.h>
#include <util/timer.h>

#include <filesystem>
#include <format>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "engine/application/Application.h"
#include "engine/graphics/VertexArray.h"
#include "glad/glad.h"
#include "layers/DebugLayer.h"

class Game {
public:
    PerspectiveCamera mainSceneCamera;

    void run() {
        Ptr<PianoCore::Application> pianoApp = PianoCore::Application::Create();

        pianoApp->PushLayer(std::make_shared<PianoApp::PianoAppGameLayer>(
            mainSceneCamera, *pianoApp));
        pianoApp->PushLayer(std::make_shared<PianoApp::PianoAppDebugLayer>(
            mainSceneCamera, *pianoApp));

        pianoApp->Start();
    }
};

int main() {
    Game game;
    game.run();
}