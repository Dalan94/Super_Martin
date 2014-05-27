/*!
 * \file menu.h
 * \brief header de menu.c
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef MENU_H
#define MENU_H


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


#include "const.h"
#include "text.h"
#include "sound.h"
#include "share.h"
#include "image.h"
#include "input.h"



/*prototypes*/

/**
 *\fn int titleMenu(SDL_Surface *screen,int *go,Sound *sound_sys, Input *in);
 *print the title menu on the screen
 *\param[out] screen the game screen
 *\param[in,out] go main loop validation
 *\param[out] sound_sys sound
 *\param[in,out] in the input structure
 *\return 1 if the enter key has been pushed
 */
int titleMenu(SDL_Surface *screen,int *go,Sound *sound_sys, Input *in);

/**
 *\fn Uint32 blinkText(Uint32 interval, void *param)
 *toggle the printing text boolean (timer callback function)
 *\param[in] interval the interval between two callback of the function
 *\param[in] param a parameter
 *\return 1000 if the boolean is right, 600 if not
 */
Uint32 blinkText(Uint32 interval, void *param);

/**
 *\fn int mainMenu(SDL_Surface *screen,int *go,Sound *sound_sys, char *player_name, Input *in)
 *print the main menu on the screen
 *\param[out] screen the game screen
 *\param[in,out] go main loop validation
 *\param[out] sound_sys sound system
 *\param[in] player_name the current player name
 *\param[in,out] in the input structure
 *\return the number of the menu which is choosen, -1 if esc
 */
int mainMenu(SDL_Surface *screen,int *go,Sound *sound_sys, char *player_name, Input *in);

/**
 *\fn int menuPlayers(SDL_Surface *screen,char player_name[MAX_SIZE_FILE_NAME],int *go,Sound *sound_sys,Input *in)
 *  Menu to choose the player
 *\param[out] screen game screen
 *\param[out] player_name the name of the current player
 *\param[in,out] go main loop validation
 *\param[in,out] sound_sys the sound system
 *\param[in,out] in the input structure
 *\return 2 if the option NewPlayer has been choosen, 1 if a player has been choosen, -1 if esc
 */

int menuPlayers(SDL_Surface *screen, char player_name[MAX_SIZE_FILE_NAME], int *go, Sound *sound_sys, Input *in);

#endif // MENU_H
