
/*!
 * \file game.h
 * \brief game.c header
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
#include "text.h"
#include "sound.h"
#include "share.h"
#include "character.h"
#include "file_level.h"
#include "image.h"
#include "map.h"
#include "input.h"
#include "mobile_platform.h"



/*prototypes*/

int play(SDL_Surface *screen,char *level_name,Sound *sound_sys,int *go,SDLKey *kc,Input *in);
void printGameOver(SDL_Surface *screen, int* continuer,Input *in,Sound *sound_sys);


void move (float move_left, float move_right,int jump, Character *player,Map *m,float* speed, int *acceleration,list *l,Sound *s,platformSet *ps);

void printWin(SDL_Surface *screen,int *continuer,Input *in,Sound *sound_sys);

void updateSpeed(float *speed, int acceleration);
void printPause(SDL_Surface *screen, Input *in, int *time, int *go,SDLKey *kc);
Uint32 decomptage(Uint32 intervalle,void* parametre);
void printHUD(SDL_Surface *screen,Character *player,Map *m);

#endif // JEU_H_INCLUDED
