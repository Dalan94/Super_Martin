
/*!
 * \file jeu.h
 * \brief header de jeu.c
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
#include "player.h"
#include "file_level.h"

#define POURCENTAGE_DEPLACEMENT 15

/*prototypes*/
void jouer(SDL_Surface *screen,char *level_name);
void updateScreenMap(SDL_Surface *screen, Map *m,char *tileset);
void scrolling(Map *m,int direction,float speed);
Uint32 decomptage(Uint32 intervalle,void* parametre);
Map* initMap(Level *lvl,SDL_Surface *screen);
void freeMap(Map *m);
void printGameOver(SDL_Surface *screen, int* continuer);
void move (int move_left, int move_right, Character *player,Map *m,float speed, int *acceleration);
void updateSpeed(float *speed, int acceleration);
void printPause(SDL_Surface *screen, SDL_Event *event);
#endif // JEU_H_INCLUDED
