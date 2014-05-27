/*!
 * \file map.h
 * \brief  map.c header
 * \author Xavier COPONET, Glenn HERROU
 * \date 2014-05-18
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

/**
 *\fn void updateScreenMap(SDL_Surface *screen, Map *m, char *tileset, Cursor *cursor)
 *update and display the map on the screen
 *\param[in,out] screen The screen of the game
 *\param[in] m The map
 *\param[in] tileset The level tileset
 *\param[in] cursor The mouse cursor
 */

void updateScreenMap(SDL_Surface *screen, Map *m,char *tileset, Cursor *cursor);

/**
 *\fn  Map *initMap(SDL_Surface *screen,char * level_name)
 *initialize the map
 *\param[in] screen game screen
 *\param[in] level_name lvl name
 *\return a pointer on the map
 */

Map* initMap(SDL_Surface *screen,char * level_name);

/**
 *\fn  void fillLine(Map *m, int line, int column, char tileID)
 *Fill a line with the current tile. The filling stops if another non-void tile is reached. This function works only with ground tiles
 *\param[in] m The map
 *\param[in] line The line pointed by the cursor
 *\param[in] column The column pointed by the cursor
 *\param[in] tileID the tile ID
 */

void fillLine(Map *m, int line, int column, char tileID);

/**
 *\fn  void fillColumn(Map *m, int line, int column, char tileID)
 *Fill a column with the current tile. The filling stops if another non-void tile is reached. This function works only with ground tiles
 *\param[in] m The map
 *\param[in] line The line pointed by the cursor
 *\param[in] column The column pointed by the cursor
 *\param[in] tileID the tile ID
 */

void fillColumn(Map *m, int line, int column, char tileID);

/**
 *\fn  void fillRect(Map *m, int line, int column, char tileID)
 *Fill a rectangle with the current tile. The filling stops if another non-void tile is reached. This function works only with ground tiles
 *\param[in] m The map
 *\param[in] line The line pointed by the cursor
 *\param[in] column The column pointed by the cursor
 *\param[in] tileID the tile ID
 */

void fillRect(Map *m, int line, int column, char tileID);

/**
  *\fn void displayHelp(SDL_Surface *screen, SDLKey *kc)
  *Display the list of keybindings on the screen
  *\param[in,out] screen The screen of the game
  *\param[in] kc The array containing the keybindings
  */

void displayHelp(SDL_Surface *screen, SDLKey *kc);

/**
  *\fn void saveMap(SDL_Surface *screen, Map *m)
  *Save the map in a new file and update the file 'level' containing the map list
  *\param[in,out] screen The screen of the game
  *\param[in] m The map to save
  */

void saveMap(SDL_Surface *screen, Map *m);

/**
  *\fn void deleteMap(SDL_Surface *screen, char *map_name, char *map_path)
  *Delete a the map file and update the level list file
  *\param[in,out] screen The screen of the game
  *\param[in] map_name The name of the map to delete
  *\param[in] map_path The path to the file of the map to delete
  */

void deleteMap(SDL_Surface *screen, char *map_name, char *map_path);

/**
  *\fn void extendMap(Map *m)
  *Extend the width of a map
  *\param[out] m The map to extend
  */

void extendMap(Map *m);

/**
  *\fn void resetMap(Map *m)
  *Fill a map with blank tiles. This function doesn't change the current map file.
  *\param[in,out] m The map to reinit
  */

void resetMap(Map *m);

 /**
  *\fn void freeMap(Map *m)
  *Free memory allocated to the map
  *\param[in,out] m the map
  */

void freeMap(Map *m);
#endif // MAP_H_INCLUDED
