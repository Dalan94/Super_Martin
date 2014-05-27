/*!
 * \file    menu_level.h
 * \brief   menu_level.c header
 * \author  Remi BERTHO, Glenn HERROU
 * \date    2014-05-10
 * \version 2.0
 */

#ifndef MENU_LEVEL_H_INCLUDED
#define MENU_LEVEL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "const.h"
#include "file_level.h"
#include "share.h"
#include "text.h"
#include "image.h"
#include "input.h"

/**
 *\fn int menuLevel(SDL_Surface *screen,char level_name[MAX_LENGTH_FILE_NAME], char level_path[MAX_LENGTH_FILE_NAME])
 * Display the level menu on the screen
 *\param[out] screen The screen of the game
 *\param[out] level_name The level name
 *\param[out] level_path The level file path
 */

int menuLevel(SDL_Surface *screen,char level_name[MAX_LENGTH_FILE_NAME], char level_path[MAX_LENGTH_FILE_NAME]);


#endif // MENU_LEVEL_H_INCLUDED
