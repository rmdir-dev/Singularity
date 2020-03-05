#pragma once
#include <GLFW/glfw3.h>
#include "Utils/Event/Event.h"
#include "Utils/Event/KeyEvent.h"

using EventCallbackFct = std::function<void(Event::Event&)>;

struct EventTest
{
    EventTest();

    EventCallbackFct eventCallBack;

    void onEvent(Event::Event& e);

    bool keyPressEvent(Event::KeyPressed& e);
};

struct Test{
    static void windowInitTest();

    static void mainLoop();

    static void destroy();    

    static void KeyPressCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);

    static GLFWwindow* window;

    static EventTest eTest;
};