#include "EventHandler.h"

void EventHandler::handleEvent(SDL_Event* event) {
    switch (event->type) {
    case SDL_KEYDOWN:
        handleKeyDown(
            event->key.keysym.sym,
            event->key.keysym.scancode,
            event->key.keysym.mod);
        break;
    case SDL_KEYUP:
        handleKeyUp(
            event->key.keysym.sym,
            event->key.keysym.scancode,
            event->key.keysym.mod);
        break;
    case SDL_QUIT:
        handleExit();
        break;
    }
}
