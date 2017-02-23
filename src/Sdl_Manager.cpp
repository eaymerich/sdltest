#include <iostream>

#include "Sdl_Manager.h"

Sdl_Manager::Sdl_Manager() :
    window{nullptr},
    glcontext{0},
    width{1024},
    height{768} {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow("SDL Test",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );//| SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window) {
        std::cerr << "Window could not be created: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetSwapInterval(0); // 0 - vsync off   1 - vsync on
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    glcontext = SDL_GL_CreateContext(window);

    glFrontFace(GL_CCW); // Set triangle orientation as counter-clock wise.
    glCullFace(GL_BACK), // Cull triangles looking away from camera.
               glEnable(GL_CULL_FACE); // Activate triangle culling.
    glEnable(GL_DEPTH_TEST); // Activate depth test.
    glDepthFunc(GL_LEQUAL);
    glClearDepthf(1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

Sdl_Manager::~Sdl_Manager() {
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Sdl_Manager::swap() {
    SDL_GL_SwapWindow(window);
}

void Sdl_Manager::setViewPort(ViewPort vp) {
    switch (vp) {
        case FULL:
            glViewport(0, 0, width, height);
            break;
        case TOP_LEFT:
            glViewport(0, height/2+1, width/2, height/2);
            break;
        case TOP_RIGHT:
            glViewport(width/2+1, height/2+1, width/2, height/2);
            break;
        case BOTTOM_LEFT:
            glViewport(0, 0, width/2, height/2);
            break;
        case BOTTOM_RIGHT:
            glViewport(width/2+1, 0, width/2, height/2);
            break;
    }
}
