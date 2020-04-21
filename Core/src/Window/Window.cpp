#include "Window.h"
#include "Utils/Event/Event.h"
#include "Utils/Event/KeyEvent.h"
#include "Utils/Event/MouseEvent.h"
#include "Utils/Event/ApplicationEvent.h"
#include "Utils/Log.h"

namespace Window
{
    double Window::s_LastX = 0.0f;
    double Window::s_LastY = 0.0f;
    bool Window::s_FirstMouseInput = true;

    Window::Window(const char* name, uint width, uint height)
    {   
        CORE_INFO("Singularity Engine Start :");
        m_WindowInfo = WindowInfo(name, width, height);
        if(!Init())
        {
            CORE_CRITICAL("Failed to start the engine.\n ENGINE SHUTDOWN!");
        }
        CORE_INFO("Engine started!\n\n");
        m_Deltatime = 0.0f;
        m_LastFrame = 0.0f;
        s_LastX = width / 2;
        s_LastY = height / 2;
    }

    Window::~Window() 
    {
        
    }

    void Window::onMainLoop() 
    {
        float currentFrame = glfwGetTime();
        m_Deltatime = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;
        //Swap the framebuffer.
        glfwSwapBuffers(m_Window);
        //Polling GLFW Event
        glfwPollEvents();
    }

    void Window::ClearColor(float red, float green, float blue, float alpha) 
    {
        //Set the color value to reset the framebuffer to 
        glClearColor(red, green, blue, alpha);
        //Clear the color buffer bit & the depth buffer.(TODO)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

    void Window::SetWindowClose(bool value) 
    {
        glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
    }

    float Window::GetDeltaTime() 
    {
        return m_Deltatime;
    }

    bool Window::Init() 
    {
        //Start GLFW
        if(!glfwInit())
        {
            CORE_CRITICAL("Failed to initialize GLFW!");
            return 0;
        }

        //GLFW ERROR CALLBACK
        glfwSetErrorCallback(GLFWErrorCallback);

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

        //Disable Vsync
        glfwSwapInterval(0);

        //Set the User Pointer of m_Window to m_Window
        glfwSetWindowUserPointer(m_Window, &m_WindowInfo);

        //Disable the mouse cursor and lock it to the window.
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //          CALLBACKS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        //Set the Key callback.
        glfwSetKeyCallback(m_Window, KeyPressCallback);
        //Set mouse callback.
        glfwSetCursorPosCallback(m_Window, MouseMovedCallback);
        //Set framebuffer resize callback
        glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
        
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

        //Enable Depth testing (3D)
        glEnable(GL_DEPTH_TEST); 

        // OPENGL CALLBACK
        glDebugMessageCallback(OpenGLErrorCallback, NULL);

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
            Event::KeyPressed event(key, 0);
            info.EventCallback(event);
            break;
        }

        case GLFW_RELEASE:
        {
            Event::KeyReleased event(key);
            info.EventCallback(event);
            break;
        }

        case GLFW_REPEAT:
        {
            //Event::KeyPressed event(scancode, 1);
            //info.EventCallback(event);
            break;
        }
        }
    }


    void Window::MouseMovedCallback(GLFWwindow* window, double xpos, double ypos) 
    {
        if(s_FirstMouseInput)
        {
            s_LastX = xpos;
            s_LastY = ypos;
            s_FirstMouseInput = false;
        }
        WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
        float xOffset = xpos - s_LastX;
        float YOffset = ypos - s_LastY;
        s_LastX = xpos;
        s_LastY = ypos;

        Event::MouseMoved event(xOffset, YOffset);
        info.EventCallback(event);
    }

    void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height) 
    {
        //Get the User Pointer (Else windowsInfo MUST be Static)
        WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
        info.Width = width;
        info.Height = height;

        Event::WindowResize event(width, height);
        info.EventCallback(event);

        //Chanege viewport size.
        glViewport(0, 0, width, height);
    }

    void Window::GLFWErrorCallback(int error, const char* description) 
    {
        CORE_ERROR("GLFW Error: ", error, "\n", description);
    }

    void Window::OpenGLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data) 
    {
        char* _source;
        char* _type;
        char* _severity;

        switch (source)
        {
        case GL_DEBUG_SOURCE_API:
            _source = "API";
            break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            _source = "WINDOW SYSTEM";
            break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            _source = "SHADER COMPILER";
            break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            _source = "THIRD PARTY";
            break;

        case GL_DEBUG_SOURCE_APPLICATION:
            _source = "APPLICATION";
            break;

        case GL_DEBUG_SOURCE_OTHER:
            _source = "UNKNOWN";
            break;

        default:
            _source = "UNKNOWN";
            break;
        }

        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            _type = "ERROR";
            break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            _type = "DEPRECATED BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            _type = "UDEFINED BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_PORTABILITY:
            _type = "PORTABILITY";
            break;

        case GL_DEBUG_TYPE_PERFORMANCE:
            _type = "PERFORMANCE";
            break;

        case GL_DEBUG_TYPE_OTHER:
            _type = "OTHER";
            break;

        case GL_DEBUG_TYPE_MARKER:
            _type = "MARKER";
            break;

        default:
            _type = "UNKNOWN";
            break;
        }

        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            _severity = "HIGH";
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            _severity = "MEDIUM";
            break;

        case GL_DEBUG_SEVERITY_LOW:
            _severity = "LOW";
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            _severity = "NOTIFICATION";
            break;

        default:
            _severity = "UNKNOWN";
            break;
        }
        char buffer[100];
        sprintf(buffer, "%d: %s of %s severity, raised from %s: %s\n",
            id, _type, _severity, _source, msg);

        //TODO OPTIMIZE
        std::string out = buffer;
        CORE_ERROR(out);
    }
}



