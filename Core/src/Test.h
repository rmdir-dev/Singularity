#pragma once
#include <GLFW/glfw3.h>

struct Test{
    static void windowInitTest();

    static void mainLoop();

    static void destroy();

    static void KeyPressCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);

    static GLFWwindow* window;
};