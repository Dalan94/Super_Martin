#include "share.h"

/**
 *\fn void waitFPS(int *previous_time, int *current_time)
 *  Permet d'attendre le temps necessaire pour avoir le nombre de PFS souhaité
 *\param[in,out] previous_time le temps precedent
 *\param[in,out] previous_time le temps actuel
 */
void waitFPS(int *previous_time, int *current_time)
{
    *current_time=SDL_GetTicks();
    if (*current_time-*previous_time < 1000/FPS)
        SDL_Delay(1000/FPS-(*current_time-*previous_time));
    *previous_time=SDL_GetTicks();
}
