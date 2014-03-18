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
int menu(SDL_Surface *screen,int *continuer,Sound *s);
Uint32 blinkText(Uint32 intervalle, void *parametre);


#endif // MENU_H
