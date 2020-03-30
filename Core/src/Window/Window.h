#pragma once

#include <Utils/pch.h>
#include <Utils/Event/Event.h>
#include <GLFW/glfw3.h>
#include <memory>

using EventCallbackFct = std::function<void(Event::Event&)>;

namespace Window 
{
    struct WindowInfo
    {
        uint Height, Width;
        String Title;
        bool Vsync, Closed;
        EventCallbackFct EventCallback;

        WindowInfo(const char*title = "Test Window",
                    uint width = 1280,
                    uint height = 720,
                    bool vsync = true)
            : Title(title), Width(width), Height(height), Vsync(vsync), Closed(false)           
        {}
    };

    class Window
    {    
    public:
        Window(const char* name, uint width, uint height);
        ~Window();

        void onMainLoop();

        void CloseWindow(); 

        void SetEventCallback(const EventCallbackFct& callback);

        bool IsWindowClose();       

    private:
        bool Init();

        void Destroy();

    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //!!!!!STATIC CALLBACK!!!!!!
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
        static void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //!!!!!!!!VARIABLES!!!!!!!!!
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    private:
        static WindowInfo s_WindowInfo;
        static GLFWwindow* s_Window;
        //static std::unique_ptr<Window> s_Instance;
    };
}