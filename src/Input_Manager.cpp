#include <SDL2/SDL.h>

#include "Goon.h"
#include "Input_Manager.h"

Input_Manager::Input_Manager() :
    eventHandler{nullptr}
{}

void Input_Manager::setEventHandler(EventHandler* handler) {
    eventHandler = handler;
}

void Input_Manager::readInput() {
    SDL_Event event;
    if (eventHandler) {
        while (SDL_PollEvent(&event)) {
            eventHandler->handleEvent(&event);
        }
    }
}
