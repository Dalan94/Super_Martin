
/*!
 * \file game.h
 * \brief game.c header
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "const.h"
#include "text.h"
#include "sound.h"
#include "share.h"
#include "character.h"
#include "file_level.h"
#include "image.h"
#include "map.h"
#include "input.h"
#include "mobile_platform.h"
#include "projectile.h"
#include "player.h"
#include "enemies.h"



/*prototypes*/

/**
 *\fn int play(SDL_Surface *screen,char *level_name,Sound *sound_sys,int *go,SDLKey *kc, Input *in, Player *player, char player_name[MAX_SIZE_FILE_NAME], int currentLevel, int nb_lvl)
 *initialize a game map and contain the main loop for the game
 *\param[in,out] screen the gamin screen
 *\param[in] level_name the name of the level to be played
 *\param[out] sound_sys the game sound system
 *\param[in] kc the keyboard configuration structure
 *\param[in,out] go the software main loop validation
 *\param[in,out] in the input gestion structure
 *\param[in,out] player the save player structure
 *\param[in] player_name the current player name
 *\param[in] nb_lvl the number of level
 *\param[in] currentLevel the current level
 *\return 1 if the maryo dies, 0 if he wins or if he quits the level
 */
int play(SDL_Surface *screen,char *level_name,Sound *sound_sys,int *go,SDLKey *kc, Input *in, Player *player, char player_name[MAX_SIZE_FILE_NAME], int currentLevel, int nb_lvl);

/**
 *\fn void printGameOver(SDL_Surface *screen,int *go,Input *in,Sound *sound_sys)
 *print the game over screen and wait until the player press a key
 *\param[out] screen the game screen
 *\param[out] go the game function main loop validation
 *\param[in,out] in the input structure
 *\param[out] sound_sys the sound system
 */
void printGameOver(SDL_Surface *screen, int* go,Input *in,Sound *sound_sys);

/**
 *\fn void move(float move_left, float move_right,int jump, Character *player,Map *m,float *speed, int *acceleration,list *l,Sound *sound_sys,platformSet *ps)
 *  moves the player and scrolls the screen if needed
 *\param[in] move_left 1 if move to the left
 *\param[in] move_right 1 if move to the right
 *\param[in] jump 1 if jump
 *\param[in] player the player
 *\param[in] m the game map
 *\param[in] speed the movement speed
 *\param[out] acceleration the acceleration of the player
 *\param[in,out] l the enemy list
 *\param[out] sound_sys the game sound system
 *\param[out] ps the platform set
 */
void move(float move_left, float move_right,int jump, Character *player,Map *m,float *speed, int *acceleration,list *l,Sound *sound_sys,platformSet *ps);

/**
 *\fn void printWin(SDL_Surface *screen,int *go,Input *in,Sound *sound_sys)
 *print the win screen and wait until the player press a key
 *\param[out] screen the game screen
 *\param[out] go the game function main loop validation
 *\param[in,out] in the input structure
 *\param[out] sound_sys the sound system
 */
void printWin(SDL_Surface *screen,int *go,Input *in,Sound *sound_sys);

/**
 *\fn void updateSpeed(float *speed, int acceleration)
 * update the player speed in correlation with its acceleration
 *\param[out] speed the player speed
 *\param[out] acceleration the player acceleration
 */
void updateSpeed(float *speed, int acceleration);

/**
 *\fn void printPause(SDL_Surface *screen,Input *in,int *time,int *go,SDLKey *kc)
 *print the pause screen and wait until the player press the pause key
 *\param[out] screen the game screen
 *\param[out] go the game function main loop validation
 *\param[in,out] in the input structure
 *\param[in] time the current time of the level
 *\param[in] kc the keyboard configuration
 */
void printPause(SDL_Surface *screen, Input *in, int *time, int *go,SDLKey *kc);

/**
 *\fn Uint32 decrement(Uint32 interval,void* parameter)
 *the callback function to decrement the time indicator
 *\param[in] interval the interval between two calls of the function
 *\param[out] parameter the time indicator
 *\return the interval between two calls of the function
 */
Uint32 decrement(Uint32 interval,void* parameter);

/**
 *\fn Uint32 rocketLaunch(Uint32 interval,void* parameter)
 *the callback function to flip the rocket launch validation
 *\param[in] interval the interval between two calls of the function
 *\param[out] parameter the launch validation
 *\return the interval between two calls of the function
 */
Uint32 rocketLaunch(Uint32 interval,void* parameter);

/**
 *\fn void printHUD(SDL_Surface *screen,Character *player,Map *m)
 *print the player HUD on the screen
 *\param[in,out] screen the game screen
 *\param[in] player the player
 *\param[in] m the game map
 */
void printHUD(SDL_Surface *screen,Character *player,Map *m);

#endif // JEU_H_INCLUDED
