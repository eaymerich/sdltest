#include <iostream>

#include "Sdl_Manager.h"
#include "Input_Manager.h"
#include "Goon.h"
#include "TestTriangle.h"
#include "TestCube.h"
#include "FlatCube.h"
#include "PhongCube.h"
#include "Camera.h"

int main() {
    std::cout << "Hello SDL Test v0.1" << std::endl;

    // Init SDL and OpenGL ES 2.0
    Sdl_Manager sdl;
    Goon goon;
    Input_Manager input_manager;

    // Init game objects
    Camera camera{glm::vec3{0.0f, 1.5f, 1.5f}};
    Camera cameraFront{glm::vec3{0.0f, 0.0f, 2.0f}}; // Camera from Z (front)
    Camera cameraSide{glm::vec3{2.0f, 0.0f, 0.0f}}; // Camera from X (side)
    Camera cameraTop{glm::vec3{0.0f, 2.0f, 0.0f},
                     glm::vec3{0.0f, 0.0f, 0.0f},
                     glm::vec3{0.0f, 0.0f, -1.0f}}; // Camera from Y (top)
    TestTriangle triangle;
    //TestCube cube;
    PhongCube fcube;

    // Game Cycle
    while (goon()) {
        // Read Input
        input_manager.readInput();

        // Logic
        uint32_t count = SDL_GetTicks();
        //camera.update();
        fcube.update(count);

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sdl.setViewPort(TOP_LEFT);
        Camera::setCurrentCamera(cameraFront);
        fcube.draw();

        sdl.setViewPort(TOP_RIGHT);
        Camera::setCurrentCamera(cameraSide);
        fcube.draw();

        sdl.setViewPort(BOTTOM_LEFT);
        Camera::setCurrentCamera(cameraTop);
        fcube.draw();

        sdl.setViewPort(BOTTOM_RIGHT);
        Camera::setCurrentCamera(camera);
        fcube.draw();


        sdl.swap();

        //SDL_Delay(150);
    }

    return 0;
}
