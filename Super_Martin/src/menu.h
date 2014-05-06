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
int titleMenu(SDL_Surface *screen,int *go,Sound *s);
Uint32 blinkText(Uint32 interval, void *param);
int mainMenu(SDL_Surface *screen,int *go,Sound *sound_sys, char *player_name);
int menuPlayers(SDL_Surface *screen, char player_name[MAX_SIZE_FILE_NAME], int *go, Sound *sound_sys);

#endif // MENU_H
