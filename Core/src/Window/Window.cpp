#include "Window.h"
#include "Utils/Event/Event.h"
#include "Utils/Event/KeyEvent.h"
#include "Utils/Event/MouseEvent.h"
#include "Utils/Event/ApplicationEvent.h"

namespace Window
{
    WindowInfo Window::s_WindowInfo;
    GLFWwindow* Window::s_Window;
    

    Window::Window(const char* name, uint width, uint height)
    {
        s_WindowInfo = WindowInfo(name, width, height);
        Init();
    }

    Window::~Window() 
    {
        
    }

    void Window::onMainLoop() 
    {
        glfwPollEvents();
    }

    void Window::CloseWindow() 
    {
        glfwDestroyWindow(s_Window);
        glfwTerminate();
    }

    void Window::SetEventCallback(const EventCallbackFct& callback) 
    {
        s_WindowInfo.EventCallback = callback;
    }

    bool Window::IsWindowClose() 
    {
        return !glfwWindowShouldClose(s_Window);
    }

    bool Window::Init() 
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        s_Window = glfwCreateWindow(800, 600, "Test window", nullptr, nullptr);

        glfwSetWindowUserPointer(s_Window, s_Window);

        glfwSetKeyCallback(s_Window, KeyPressCallback);
    }

    void Window::Destroy() 
    {
        
    }

    void Window::KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
    {
        switch(action)
        {
        case GLFW_PRESS:
        {
            Event::KeyPressed event(scancode, 0);
            s_WindowInfo.EventCallback(event);
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

