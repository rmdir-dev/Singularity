#pragma once
#include "Utils/Event/Event.h"
#include "Utils/Event/KeyEvent.h"
#include "Window/Window.h"
#include "Layer/TestLayer.h"

struct Test{
    Test();
    
    ~Test();

    void windowInitTest();

    void mainLoop();

    void destroy();

    void ImGUISetup();

    void ImGUIRenderBeging();

    void ImGUIRenderEnd();

    void onEvent(Event::Event& e); 

    bool keyPressEvent(Event::KeyPressed& e); 

    std::unique_ptr<Window::Window> Window;
    std::unique_ptr<Layer::TestLayer> tl;

    bool ImGUI_Render = false;
};