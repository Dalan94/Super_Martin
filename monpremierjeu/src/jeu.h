
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
#include "player.h"



/*prototypes*/
void jouer(SDL_Surface *screen);
void updateScreenMap(SDL_Surface *screen, Map *m);
void scrolling(Map *m,int direction);
Uint32 decomptage(Uint32 intervalle,void* parametre);
Map* initMap(int nbBlocLgMap, int nbBlocHtMap,SDL_Surface *screen);
void freeMap(Map *m);
void printGameOver(SDL_Surface *screen, int* continuer);

#endif // JEU_H_INCLUDED
