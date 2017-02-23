#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>

enum ViewPort {
    FULL,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
};

class Sdl_Manager final
{
public:
    Sdl_Manager();
    virtual ~Sdl_Manager();
    void swap();
    void setViewPort(ViewPort vp);
private:
    SDL_Window* window;
    SDL_GLContext glcontext;
    GLsizei width;
    GLsizei height;
};

#endif // SDL_MANAGER_H
