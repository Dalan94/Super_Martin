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
int menu(SDL_Surface *screen,int *choice);
int menuTileSet(SDL_Surface *screen, char tileSet_name[MAX_LENGTH_FILE_NAME]);


#endif // MENU_H
