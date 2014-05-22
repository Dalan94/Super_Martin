/*!
 * \file    player.h
 * \brief   player.c header
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


/**
 *\fn int newPlayer(SDL_Surface *screen,char player_name[MAX_SIZE_FILE_NAME],Sound *s,int *go)
 *Display the interface to create a new player
 *\param[in,out] screen The screen of the game
 *\param[out] player_name The name of the new player
 *\param[out] s the sound system
 *\param[out] go the main loop validation
 *\return 1 if a new player has been created, 0 otherwise
 */

int newPlayer(SDL_Surface *screen,char player_name[MAX_SIZE_FILE_NAME],Sound *s,int *go);

/**
 *\fn void loadPlayer(char fileSave[MAX_SIZE_FILE_NAME], char player_name[MAX_SIZE_FILE_NAME], Player *player)
 *Load the progression of the given player from the binary file named fileSave
 *\param[in] fileSave The path to the binary file containing the progression of each player
 *\param[in] player_name The name of the current player
 *\param[out] player The player structure where the progression will be loaded
 */

void loadPlayer(char fileSave[MAX_SIZE_FILE_NAME], char player_name[MAX_SIZE_FILE_NAME], Player *player);

/**
 *\fn int savePlayer(char fileSave[MAX_SIZE_FILE_NAME], char player_name[MAX_SIZE_FILE_NAME], Player *player)
 *Save the progression of the given player in the binary file named fileSave
 *\param[in] fileSave The path to the binary file containing the progression of each player
 *\param[in] player_name The name of the current player
 *\param[out] player The player structure where the progression is stored
 */

int savePlayer(char fileSave[MAX_SIZE_FILE_NAME], char player_name[MAX_SIZE_FILE_NAME], Player *player);

/**
 *\fn void save(SDL_Surface *screen, char fileSave[MAX_SIZE_FILE_NAME], char player_name[MAX_SIZE_FILE_NAME], Player *player, int *go)
 *Display the interface to save the player progression
 *\param[in, out] screen The screen of the game
 *\param[in] fileSave The path to the binary file containing the progression of each player
 *\param[in] player_name The name of the current player
 *\param[out] player The player structure where the progression is stored
 *\param[out] go The main loop validation
 */

void save(SDL_Surface *screen, char fileSave[MAX_SIZE_FILE_NAME], char player_name[MAX_SIZE_FILE_NAME], Player *player, int *go);




#endif // PLAYER_H_INCLUDED
