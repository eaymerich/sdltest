#include "Goon.h"
#include "Time.h"

#include "ShipController.h"

ShipController::ShipController(PhongShip* aShipModel) :
    goLeft{false},
    goRight{false},
    goUp{false},
    goDown{false},
    horizontalSpeed{2.0},
    verticalSpeed{2.0},
    shipModel{aShipModel}
{}

void ShipController::update() {
    if (goLeft || goRight || goUp || goDown){
        auto secs = Time::getElapsedTime();
        auto pos = shipModel->getPosition();

        if (goLeft) {
            pos.x -= horizontalSpeed * secs;
        }

        if (goRight) {
            pos.x += horizontalSpeed * secs;
        }

        if (goUp) {
            pos.y += verticalSpeed * secs;
        }

        if (goDown) {
            pos.y -= verticalSpeed * secs;
        }

        shipModel->setPosition(pos);
    }
}

void ShipController::handleKeyDown(
    SDL_Keycode sym, SDL_Scancode scancode, Uint16 mod) {
    (void)(scancode);
    (void)(mod);

    switch(sym) {
    case SDLK_ESCAPE:
        Goon::stop();
        break;
    case SDLK_LEFT:
        goLeft = true;
        goRight = false;
        break;
    case SDLK_RIGHT:
        goLeft = false;
        goRight = true;
        break;
    case SDLK_UP:
        goUp = true;
        goDown = false;
        break;
    case SDLK_DOWN:
        goUp = false;
        goDown = true;
        break;
    }
}

void ShipController::handleKeyUp(
    SDL_Keycode sym, SDL_Scancode scancode, Uint16 mod) {
    (void)(scancode);
    (void)(mod);

    switch(sym) {
    case SDLK_LEFT:
        goLeft = false;
        break;
    case SDLK_RIGHT:
        goRight = false;
        break;
    case SDLK_UP:
        goUp = false;
        break;
    case SDLK_DOWN:
        goDown = false;
        break;
    }
}

void ShipController::handleExit() {
    Goon::stop();
}
