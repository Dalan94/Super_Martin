/*!
 * \file    share.h
 * \brief   share.c header
 * \author  Remi BERTHO
 * \date    15/03/14
 * \version 1.0
 */

#ifndef SHARE_H_INCLUDED
#define SHARE_H_INCLUDED

#include "const.h"
#include <SDL/SDL.h>

/**
 *\fn void waitFPS(int *previous_time, int *current_time)
 *Function managing the fps rate
 *\param[in,out] previous_time The previous time
 *\param[in,out] current_time The current time
 */

void waitFPS(int *previous_time,int *current_time);

#endif
