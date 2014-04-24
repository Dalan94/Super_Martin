/*!
 * \file    menu_level.h
 * \brief   Menu gerant le choix du niveau
 * \author  Remi BERTHO
 * \date    15/03/14
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
#include "sound.h"
#include "image.h"
#include "input.h"

int menuLevel(SDL_Surface *screen,char level_name[MAX_LENGTH_FILE_NAME], char level_path[MAX_LENGTH_FILE_NAME]);


#endif // MENU_LEVEL_H_INCLUDED
