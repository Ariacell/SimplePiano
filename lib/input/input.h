#pragma once

namespace Input
{
    class InputManager
    {
    public:
        void keyCallback(int key, int action);
        bool isDebugWindowVisible() const;

    private:
        bool debugWindowVisible = false;
    };
}