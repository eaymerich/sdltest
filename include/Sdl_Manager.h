#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>

class Sdl_Manager final
{
public:
    Sdl_Manager();
    virtual ~Sdl_Manager();
    void swap();
private:
    SDL_Window* window;
    SDL_GLContext glcontext;
};

#endif // SDL_MANAGER_H
