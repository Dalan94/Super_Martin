/*!
 * \file map.h
 * \brief Header of map.c
 * \author Xavier COPONET, Glenn HERROU
 * \date 2014-03-18
 */

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "const.h"

void updateScreenMap(SDL_Surface *screen, Map *m,char *tileset, Cursor *cursor);
void scrolling(Map *m,int direction);
Map* initMap(Level *lvl,SDL_Surface *screen);
void saveMap(Map *m);
void cleanString(const char *buffer, FILE *fp);
void clean_stdin(void);
void reinitMap(Map *m);
void freeMap(Map *m);

#endif // MAP_H_INCLUDED

