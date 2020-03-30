#pragma once
#include <GLFW/glfw3.h>
#include "Utils/Event/Event.h"
#include "Utils/Event/KeyEvent.h"
#include "Window/Window.h"

struct Test{
    Test();
    
    ~Test();

    void windowInitTest();

    void mainLoop();

    void destroy();

    void onEvent(Event::Event& e); 

    bool keyPressEvent(Event::KeyPressed& e); 

    std::unique_ptr<Window::Window> Window;
};