
/*!
 * \file game.h
 * \brief header de game.c
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "const.h"
#include "structures.h"
#include "text.h"
#include "sound.h"
#include "share.h"
#include "file_level.h"
#include "image.h"
#include "map.h"
#include "input.h"

/*prototypes*/
void play(SDL_Surface *screen,char *level_name, SDLKey *kc);
void printGameOver(SDL_Surface *screen, int* continuer,Input *in);
void printPause(SDL_Surface *screen, Input *in, int *time, int *continuer);
Uint32 decomptage(Uint32 intervalle,void* parametre);
#endif // JEU_H_INCLUDED
