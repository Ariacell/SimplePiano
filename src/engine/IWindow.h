#pragma once
#include <functional>

namespace Engine
{
    using GLProcAddress = void *(*)(const char *);
    class IWindow
    {
    public:
        virtual ~IWindow() = default;

        virtual void Create(int width, int height, const char *title) = 0;
        virtual void SetKeyCallback(std::function<void(int key, int action, int mods)> callback) = 0;
        virtual void PollEvents() = 0;
        virtual bool ShouldClose() const = 0;
        virtual void SwapBuffers() = 0;
        virtual void GetFrameBufferSize() = 0;


        virtual GLProcAddress GetWindowProcAddress() = 0;
        virtual void *GetNativeHandle() = 0; // platform-specific pointer
    };
}