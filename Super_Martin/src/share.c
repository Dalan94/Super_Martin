#include "share.h"


void waitFPS(int *previous_time, int *current_time)
{
    *current_time=SDL_GetTicks();
    if (*current_time-*previous_time < 1000/FPS)
        SDL_Delay(1000/FPS-(*current_time-*previous_time));
    *previous_time=SDL_GetTicks();
}
