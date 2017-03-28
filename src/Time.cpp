#include <SDL2/SDL.h>
#include "Time.h"

float Time::elapsedTime = 0.0f;

Time::Time():
    lastTicks{0}
{}

void Time::update(){
    auto currentTicks = SDL_GetTicks();
    elapsedTime = (float)(currentTicks - lastTicks) * 0.001f;
    lastTicks = currentTicks;
}
