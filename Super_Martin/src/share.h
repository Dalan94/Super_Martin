/*!
 * \file    share.h
 * \brief   Gestion des fichiers de carte
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
 *  Permet d'attendre le temps necessaire pour avoir le nombre de PFS souhaité
 *\param[in,out] previous_time le temps precedent
 *\param[in,out] previous_time le temps actuel
 */
void waitFPS(int *previous_time,int *current_time);

#endif
