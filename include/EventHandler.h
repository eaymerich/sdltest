#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include <SDL2/SDL.h>

class EventHandler {
public:
    EventHandler() {}
    virtual ~EventHandler() = default;
    virtual void handleEvent(SDL_Event* event);
    virtual void handleKeyDown(
        SDL_Keycode sym, SDL_Scancode scancode, Uint16 mod) {
        // This code is just to avoid compiler warnings.
        (void)(sym);
        (void)(scancode);
        (void)(mod);
    }
    virtual void handleKeyUp(
        SDL_Keycode sym, SDL_Scancode scancode, Uint16 mod) {
        // This code is just to avoid compiler warnings.
        (void)(sym);
        (void)(scancode);
        (void)(mod);
    }
    virtual void handleExit() {}
};

#endif // __EVENT_HANDLER_H__
