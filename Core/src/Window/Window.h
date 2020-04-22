#pragma once

#include <Utils/pch.h>
#include <Utils/Event/Event.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <memory>

using EventCallbackFct = std::function<void(Event::Event&)>;

namespace Window 
{
    /*
    Window info contains :
        - Width and Height of the window
        - Title  of the window
        - Vsync is VSync on or off
        - Closed is Window close
        - EventCallback the callback function for the events
    */
    struct WindowInfo
    {
        String Title;
        uint Height, Width;
        bool Vsync, Closed;
        EventCallbackFct EventCallback;
        bool mouseCapture;

        /*
        Constructor for WindowInfo.
        Args :
        - Title the window title
        - Width the window with
        - Height the window height
        - Vsync is Vsync on or off
        - Closed is the window closed or not DEFAULT false
        */
        WindowInfo(const char*title = "Test Window",
                    uint width = 1280,
                    uint height = 720,
                    bool vsync = true)
            : Title(title), Height(height), Width(width), Vsync(vsync), Closed(false)          
        {}
    };

    class Window
    {    
    public:
        /*
        Args:
            - name : window title
            - width and height ; size in pixel of the window
        */
        Window(const char* name, uint width, uint height);
        ~Window();

        /*
        GLFW Main loop function
        */
        void onMainLoop();
        
        /*
        set clear color and clear color buffer bit;
        */
        void ClearColor(float red, float green, float blue, float alpha);

        /*
        Close GLFW window and kill GLFW process,
        */
        void CloseWindow(); 

        /*
        Set eventCallback for the event manager (eg: key push callback)
        */
        virtual void SetEventCallback(const EventCallbackFct& callback);

        /*
        return the status of the window, false if the window is closed.
        */
        bool IsWindowClose();   

        /*
        Set the close variable to true.
        */    
        void SetWindowClose(bool value);

        /*
        Return the deltatime.
        */
        float GetDeltaTime();

        /*
        Get the window
        */
        GLFWwindow* GetWindow();

    private:
        /*
        GLFW Initializtion
        */
        bool Init();

        /*
        GLFW destroy, kill GLFW process.
        */
        void Destroy();

    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //!!!!!STATIC CALLBACK!!!!!!
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //KEYBOARD
        /*
        Callback when a key is pressed.
        */
        static void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        //MOUSE
        /*
        Callback when the mouse is moved.
        */
        static void MouseMovedCallback(GLFWwindow* window, double xpos, double ypos);

        //WINDOW

        //FRAMEBUFFER
        /*
        Callback when the Framebuffer size changes.
        */
        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

        //GLFW
        static void GLFWErrorCallback(int error, const char* description);

        //OPENGL
        static void OpenGLErrorCallback(GLenum source, GLenum type, GLuint id, 
                                        GLenum severity, GLsizei length, const GLchar* msg, const void* data);

    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //!!!!!!!!VARIABLES!!!!!!!!!
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    private:
        //Window informations.
        WindowInfo m_WindowInfo;
        //GLFW Window.
        GLFWwindow* m_Window;

        //Deltatime
        float m_Deltatime;
        //Deltatime
        float m_LastFrame;

        //MOUSE POSITION X
        static double s_LastX;
        //MOUSE POSITION Y
        static double s_LastY;
        static bool s_FirstMouseInput;

        bool m_MouseCapture;
    };
}