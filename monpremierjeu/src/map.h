/*!
 * \file map.h
 * \brief header de map.c
 * \author Xavier COPONET
 * \date 2014-03-18
 */


#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "image.h"
#include "file_level.h"


/*prototypes*/
void updateScreenMap(SDL_Surface *screen, Map *m,char *tileset);
void scrolling(Map *m,int direction,float speed);
Map* initMap(SDL_Surface *screen,char * level_name);
void freeMap(Map *m);

#endif // MAP_H_INCLUDED
