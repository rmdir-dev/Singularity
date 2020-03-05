#include "Test.h"
#include "Utils/Timer.h"
#include "Utils/Log.h"
#include <iostream>


GLFWwindow* Test::window = nullptr;
EventTest Test::eTest;

void Test::windowInitTest(){
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(800, 600, "Test window", nullptr, nullptr);

    glfwSetWindowUserPointer(window, window);

    glfwSetKeyCallback(window, KeyPressCallBack);

    
}

void Test::mainLoop(){
    Timer t;
    while(!glfwWindowShouldClose(window))   
    {
        glfwPollEvents();
    }
}

void Test::destroy(){
    glfwDestroyWindow(window);
    glfwTerminate();
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
    std::cout << e.getKeyCode() << "\n";
	return true;
}

void Test::KeyPressCallBack(GLFWwindow* window, int key, int scancode, int action, int mods){
    switch(action)
    {
    case GLFW_PRESS:
    {
    	Event::KeyPressed event(key, 0);
    	eTest.eventCallBack(event);
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
