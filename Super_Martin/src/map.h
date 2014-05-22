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

/*prototypes*/
/**
 *\fn void updateScreenMap(SDL_Surface *screen, Map *m,char *tileset)
 *update and display the map
 *\param[in,out] game screen
 *\param[in] Map *m The map
 *\param[in] tileset the level tileset
 */
void updateScreenMap(SDL_Surface *screen, Map *m, char *tileSet);

/**
 *\fn void scrolling(Map *m,int direction,float speed)
 *scroll the map
 *\param[in,out] map the lvl
 *\param[in] direction scrolling direction
 *\param[in] speed scrolling speed
 */
void scrolling(Map *m,int direction,float speed);

/**
 *\fn  Map *initMap(SDL_Surface *screen,char * level_name,list *l,platformSet *ps)
 *initialize the map
 *\param[in] screen game screen
 *\param[in] level_name lvl name
 *\param[out] l the enemy list that stocks the enemies
 *\param[out] ps the platform set for the mobile platforms
 *\return pointer on the map
 */
Map* initMap(SDL_Surface *screen,char * level_name, list *l,platformSet *ps);


 /**
  *\fn void freeMap(map *m)
  *free memory allocated to the map
  *\param[in,out] m the map
  */
void freeMap(Map *m);

/**
 *\fn int collisionMap(SDL_Rect r,Map *m)
 *determine if there is a collision beteewen a sprite and a "wall" of the map
 *\param[in] r SDL_Rect corresponding to the sprite
 *\param[in] m map
 *\return 1 if there is a collision, 0 if not,2 if collision with star/coin, 3 if spring
 */
int collisionMap(SDL_Rect r,Map *m);

#endif // MAP_H_INCLUDED
