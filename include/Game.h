#ifndef __GAME_H__
#define __GAME_H__

#include "EventHandler.h"
#include "Goon.h"
#include "Input_Manager.h"
#include "Sdl_Manager.h"
#include "Time.h"

class Game : public EventHandler {
public:
    Game();
    virtual ~Game() = default;
    virtual void start();
    virtual void handleExit() override;
    virtual void handleKeyDown(
        SDL_Keycode sym, SDL_Scancode scancode, Uint16 mod) override;

protected:
    Sdl_Manager sdl;
    Goon goon;
    Input_Manager inputManager;
    Time time;
};

#endif // __GAME_H__
