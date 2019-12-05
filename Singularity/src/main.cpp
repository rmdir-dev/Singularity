#include "Test.h"

int main(int argc, char** argv)
{
    Test::windowInitTest();
    Test::mainLoop();
    Test::destroy();

    return 0;
}