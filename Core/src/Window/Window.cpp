#include "Window.h"
#include "Utils/Event/Event.h"
#include "Utils/Event/KeyEvent.h"
#include "Utils/Event/MouseEvent.h"
#include "Utils/Event/ApplicationEvent.h"
#include "Utils/Log.h"
#include "glad/glad.h"

namespace Window
{

    Window::Window(const char* name, uint width, uint height)
    {   
        CORE_INFO("Singularity Engine Start :");
        m_WindowInfo = WindowInfo(name, width, height);
        if(!Init())
        {
            CORE_CRITICAL("Failed to start the engine.\n ENGINE SHUTDOWN!");
        }
        CORE_INFO("Engine started!\n\n");
    }

    Window::~Window() 
    {
        
    }

    void Window::onMainLoop() 
    {
        //Polling GLFW Event
        glfwPollEvents();
    }

    void Window::CloseWindow() 
    {
        //Destroy the window
        glfwDestroyWindow(m_Window);
        //Terminate GLFW
        glfwTerminate();
        CORE_INFO("Engine shut down!\n\n");
    }

    void Window::SetEventCallback(const EventCallbackFct& callback) 
    {
        m_WindowInfo.EventCallback = callback;
    }

    bool Window::IsWindowClose() 
    {
        return !glfwWindowShouldClose(m_Window);
    }

    bool Window::Init() 
    {
        //Start GLFW
        if(!glfwInit())
        {
            CORE_CRITICAL("Failed to initialize GLFW!");
            return 0;
        }
        CORE_INFO("\tGLFW \t[OK]");
        //Make the window resizable.
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        //Create the Window.
        m_Window = glfwCreateWindow(m_WindowInfo.Width, m_WindowInfo.Height, "Test window", NULL, NULL);
        
        if(!m_Window)
        {
            CORE_CRITICAL("Failed to create the GLFW Window!");
            return 0;
        }
        CORE_INFO("\tWindow \t[OK]");

        //Create the context.
        glfwMakeContextCurrent(m_Window);

        //Set the User Pointer of m_Window to m_Window
        glfwSetWindowUserPointer(m_Window, &m_WindowInfo);

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //          CALLBACKS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        //Set the Key callback.
        glfwSetKeyCallback(m_Window, KeyPressCallback);
        
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //           OPENGL
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        
        if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            CORE_CRITICAL("Failed to initialize GLAD,\n  - check that your graphic drivers are installed.");
            return 0;
        }
        CORE_INFO("\tOpenGL \t[OK]");

        CORE_INFO("\n----------------------------------");
	    CORE_INFO("OpenGL Status:");
	    CORE_INFO("    ", (const char*)glGetString(GL_VERSION));
	    CORE_INFO("    ", (const char*)glGetString(GL_VENDOR));
	    CORE_INFO("    ", (const char*)glGetString(GL_RENDERER));
	    CORE_INFO("----------------------------------\n");

        glViewport(0, 0, m_WindowInfo.Width, m_WindowInfo.Height);

        return 1;        
    }

    void Window::Destroy() 
    {
        
    }

    void Window::KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
    {
        //Get the User Pointer (Else windowsInfo MUST be Static)
        WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);

        switch(action)
        {
        case GLFW_PRESS:
        {
            Event::KeyPressed event(scancode, 0);
            info.EventCallback(event);
            break;
        }

        case GLFW_RELEASE:
        {
            break;
        }

        case GLFW_REPEAT:
        {
            break;
        }
        }
    }
}

