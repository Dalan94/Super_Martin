/*!
 * \file    player.h
 * \brief   Management of the player system
 * \author  Glenn HERROU
 * \date    06/05/14
 * \version 1.0
 */

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "const.h"
#include "structures.h"
#include "file_level.h"
#include "share.h"
#include "text.h"
#include "sound.h"
#include "image.h"
#include "input.h"





int newPlayer(SDL_Surface *screen,char player_name[MAX_SIZE_FILE_NAME],Sound *s,int *go);
void loadPlayer(char fileSave[MAX_SIZE_FILE_NAME], char player_name[MAX_SIZE_FILE_NAME], Player *player);
int savePlayer(char fileSave[MAX_SIZE_FILE_NAME], char player_name[MAX_SIZE_FILE_NAME], Player *player);
void save(SDL_Surface *screen, char fileSave[MAX_SIZE_FILE_NAME], char player_name[MAX_SIZE_FILE_NAME], Player *player, int *go);




#endif // PLAYER_H_INCLUDED
