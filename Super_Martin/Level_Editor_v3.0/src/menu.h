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
#include "share.h"
#include "image.h"
#include "input.h"


/**
 *\fn int menu(SDL_Surface *screen, int *choice, int *go)
 *Display the menu on the screen
 *\param[out] screen the screen of the game
 *\param[out] choice the option selected
 *\param[out] go the main loop validation
 *\return 1 if an option has been selected
 */

int menu(SDL_Surface *screen,int *choice, int *go);

/**
 *\fn int menuTileSet(SDL_Surface *screen, char tileSet_name[MAX_LENGTH_FILE_NAME])
 *Display the tileset menu on the screen
 *\param[out] screen the screen of the game
 *\param[out] tileSet_name The name of the tileSet selected
 *\return 1 if a tileset has been selected
 */

int menuTileSet(SDL_Surface *screen, char tileSet_name[MAX_LENGTH_FILE_NAME]);


#endif // MENU_H
