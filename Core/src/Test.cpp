#include "Test.h"
#include "Utils/Timer.h"
#include "Utils/Log.h"
#include <iostream>
#include "glm/glm.hpp"

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
    Window = std::make_unique<Window::Window>("Test window", 1280, 720);
    Window->SetEventCallback(BIND_EVENT_FCT(Test::onEvent));
    tl = std::make_unique<Layer::TestLayer>();
}

void Test::mainLoop()
{
    Timer t(__func__);
    tl->OnStart();

    uint frame = 0;
    float timer = 0.0f;

    while(Window->IsWindowClose())
    {
        TPoint startTime = HrClock::now();

        Window->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        tl->OnRender();
        Window->onMainLoop();

        TPoint endTime = HrClock::now();
        eTime elaspeTime = endTime - startTime;
        timer += elaspeTime.count();
        frame++;
        if(timer > 1.0f)
        {
            timer = 0.0f;
            CORE_INFO("FPS: ", frame);
            frame = 0;
        }
    }
}

void Test::destroy()
{
    //Delete layers before closing the window
    //Else it won't be able to destroy it's shaders.
    tl.reset();
    Window->CloseWindow();
}

void Test::onEvent(Event::Event& e)
{
	Event::Dispatcher dispatcher(e);
	dispatcher.dispatch<Event::KeyPressed>(BIND_EVENT_FCT(Test::keyPressEvent));
    tl->OnEvent(e);
}

bool Test::keyPressEvent(Event::KeyPressed& e)
{
    CORE_INFO("EVENT TYPE ", e.toString());
    
    if(e.getKeyCode() == 9)
    {
        Window->SetWindowClose(true);
        return true;
    }

	return false;
}