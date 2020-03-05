#include "Test.h"
#include "Utils/Timer.h"
#include "Utils/Log.h"
#include <iostream>

GLFWwindow* Test::window = nullptr;

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

void Test::KeyPressCallBack(GLFWwindow* window, int key, int scancode, int action, int mods){
    CORE_INFO(scancode);
}