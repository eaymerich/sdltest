#include "Camera.h"
#include "PhongShip.h"
#include "PhongCheckersFloor.h"
#include "ShipController.h"

#include "Game.h"

Game::Game()
{
    inputManager.setEventHandler(this);
}


void Game::start() {
    // Init game objects
    Camera camera{glm::vec3{0.0f, 1.5f, 1.5f}};
    Camera cameraFront{glm::vec3{0.0f, 0.0f, 2.0f}}; // Camera from Z (front)
    Camera cameraSide{glm::vec3{2.0f, 0.0f, 0.0f}}; // Camera from X (side)
    Camera cameraTop{glm::vec3{0.0f, 2.0f, 0.0f},
                     glm::vec3{0.0f, 0.0f, 0.0f},
                     glm::vec3{0.0f, 0.0f, -1.0f}}; // Camera from Y (top)

    Camera dcam{glm::vec3{0.0f, 5.0f, 10.0f},
                glm::vec3{0.0f, 5.0f, 0.0f}};
    //TestTriangle triangle;
    //TestCube cube;
    //PhongCube fcube;

    PhongShip ship;
    ship.setPosition({0.0, 0.5, 0.0});
    ShipController shipControl{&ship};
    inputManager.setEventHandler(&shipControl);
    PhongCheckersFloor floor;

    // Game Cycle
    while (goon) {
        // Read Input
        inputManager.readInput();

        // Logic
        time.update();
        shipControl.update();
        uint32_t count = SDL_GetTicks();
        //camera.update();
        //fcube.update(count);
        ship.update(count);

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sdl.setViewPort(TOP_LEFT);
        Camera::setCurrentCamera(cameraFront);
        ship.draw();
        floor.draw();

        sdl.setViewPort(TOP_RIGHT);
        Camera::setCurrentCamera(cameraSide);
        ship.draw();
        floor.draw();

        sdl.setViewPort(BOTTOM_LEFT);
        Camera::setCurrentCamera(cameraTop);
        ship.draw();
        floor.draw();

        sdl.setViewPort(BOTTOM_RIGHT);
        Camera::setCurrentCamera(camera);
        Camera::setCurrentCamera(dcam);
        ship.draw();
        floor.draw();

        sdl.swap();

        //SDL_Delay(150);
    }
}

void Game::handleExit() {
    goon.stop();
}

void Game::handleKeyDown(
    SDL_Keycode sym, SDL_Scancode scancode, Uint16 mod) {
    (void)(scancode);
    (void)(mod);

    if (sym == SDLK_ESCAPE) {
        goon.stop();
    }
}
