#define GLFW_INCLUDE_NONE

#include <engine/application/Application.h>
#include <layers/DebugLayer.h>
#include <layers/GameLayer.h>

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