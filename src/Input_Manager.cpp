#include <SDL2/SDL.h>

#include "Goon.h"
#include "Input_Manager.h"

void Input_Manager::readInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            Goon::stop();
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                Goon::stop();
                break;
            }
        }
    }
}
