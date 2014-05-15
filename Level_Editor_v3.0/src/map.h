/*!
 * \file map.h
 * \brief  map.c header
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
#include "input.h"
#include "text.h"
#include "share.h"

/*prototypes*/
void updateScreenMap(SDL_Surface *screen, Map *m,char *tileset, Cursor *cursor);
void scrolling(Map *m,int direction,float speed);
Map* initMap(SDL_Surface *screen,char * level_name);
void fillLine(Map *m, int line, int column, char tileID);
void fillColumn(Map *m, int line, int column, char tileID);
void fillRect(Map *m, int line, int column, char tileID);
void displayHelp(SDL_Surface *screen, SDLKey *kc);
void saveMap(SDL_Surface *screen, Map *m);
void deleteMap(SDL_Surface *screen, char *map_name, char *map_path);
void extendMap(Map *m);
void printContinue(SDL_Surface *screen, Input *in, int *go);
void resetMap(Map *m);
void freeMap(Map *m);
#endif // MAP_H_INCLUDED
