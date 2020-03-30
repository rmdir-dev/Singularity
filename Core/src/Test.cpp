#include "Test.h"
#include "Utils/Timer.h"
#include "Utils/Log.h"
#include <iostream>


std::unique_ptr<Window::Window> Test::Window;
EventTest Test::eTest;

void Test::windowInitTest(){
    Window = std::make_unique<Window::Window>("Test window", 1024, 720);
}

void Test::mainLoop(){
    Timer t;
    while(Window->IsWindowClose())
    {
        Window->onMainLoop();
    }
}

void Test::destroy(){
    Window->CloseWindow();
}

EventTest::EventTest() 
{
    eventCallBack = BIND_EVENT_FCT(EventTest::onEvent);
}

void EventTest::onEvent(Event::Event& e)
{
	Event::Dispatcher dispatcher(e);
	dispatcher.dispatch<Event::KeyPressed>(BIND_EVENT_FCT(EventTest::keyPressEvent));
}

bool EventTest::keyPressEvent(Event::KeyPressed& e)
{
    CORE_INFO("EVENT TYPE ", e.toString());
	return true;
}