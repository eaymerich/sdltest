#include <iostream>

#include "Sdl_Manager.h"
#include "Input_Manager.h"
#include "Goon.h"
#include "TestTriangle.h"
#include "TestCube.h"
#include "Camera.h"

int main() {
    std::cout << "Hello SDL Test v0.1" << std::endl;

    // Init SDL and OpenGL ES 2.0
    Sdl_Manager sdl;
    Goon goon;
    Input_Manager input_manager;

    // Init game objects
    Camera camera;
    //TestTriangle triangle;
    TestCube cube;

    // Game Cycle
    while (goon()) {
        // Read Input
        input_manager.readInput();

        // Logic
        uint32_t count = SDL_GetTicks();
        cube.update(count);

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //triangle.draw();
        cube.draw();
        sdl.swap();

        //SDL_Delay(150);
    }

    return 0;
}
