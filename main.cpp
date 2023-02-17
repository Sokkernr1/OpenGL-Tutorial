
#include <iostream>
#include "src/classes/engine/windowManager.h"

int main()
{
    windowManager WindowManager = windowManager(
        "OpenGL learning",
        1200,
        600,
        4
    );

    int exitCode = WindowManager.startWindow();

    std::cout << "Exited with code " + exitCode << std::endl;
}
