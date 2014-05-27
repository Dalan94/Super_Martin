/*!
 * \file    share.c
 * \brief   Management of FPS rate
 * \author  Remi BERTHO
 * \date    15/03/14
 * \version 1.0
 */

 #include "share.h"

void waitFPS(int *previous_time, int *current_time)
{
    *current_time=SDL_GetTicks();
    if (*current_time-*previous_time < 1000/FPS)
        SDL_Delay(1000/FPS-(*current_time-*previous_time));
    *previous_time=SDL_GetTicks();
}
