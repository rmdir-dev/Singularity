#include "Test.h"
#include "Utils/Timer.h"
#include "Utils/Log.h"
#include <iostream>

Test::Test() 
{
    
}


Test::~Test() 
{
    CORE_INFO("Destroy\n");
    destroy();    
}

void Test::windowInitTest()
{
    Window = std::make_unique<Window::Window>("Test window", 1024, 720);
    Window->SetEventCallback(BIND_EVENT_FCT(Test::onEvent));
}

void Test::mainLoop()
{
    Timer t(__func__);
    while(Window->IsWindowClose())
    {
        Window->onMainLoop();
    }
}

void Test::destroy()
{
    Window->CloseWindow();
}

void Test::onEvent(Event::Event& e)
{
	Event::Dispatcher dispatcher(e);
	dispatcher.dispatch<Event::KeyPressed>(BIND_EVENT_FCT(Test::keyPressEvent));
}

bool Test::keyPressEvent(Event::KeyPressed& e)
{
    CORE_INFO("EVENT TYPE ", e.toString());
	return true;
}