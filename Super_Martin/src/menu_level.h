/*!
 * \file    menu_level.h
 * \brief   Menu gerant le choix du niveau
 * \author  Remi BERTHO
 * \date    15/03/14
 * \version 2.0
 */

#ifndef MENU_LEVEL_H_INCLUDED
#define MENU_LEVEL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "const.h"
#include "structures.h"
#include "file_level.h"
#include "share.h"
#include "text.h"
#include "sound.h"
#include "image.h"
#include "input.h"

/**
 *\fn int menuLevel(SDL_Surface *screen,char level_name[MAX_SIZE_FILE_NAME],Sound *sound_sys char player_name[MAX_SIZE_FILE_NAME], Player *player, int *go, int *nb_lvl, Input *in)
 *  Menu to choose the lvl
 *\param[out] screen game screen
 *\param[out] level_name the name of the level we will want to launch
 *\param[in,out] sound_sys the sound system
 *\param[in, out] Player the player structure
 *\param[in,out] go the soft main loop validation
 *\param[in] nb_lvl the number of level
 *\param[in,out] in the input structure
 *\return 1 if a level has been choosen, 0 if not
 */
int menuLevel(SDL_Surface *screen,char level_name[MAX_SIZE_FILE_NAME],Sound *sound_sys, char player_name[MAX_SIZE_FILE_NAME], Player *player, int *go, int *nb_lvl, Input *in);

#endif // MENU_LEVEL_H_INCLUDED
