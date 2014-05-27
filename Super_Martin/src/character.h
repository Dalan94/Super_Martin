/*!
 * \file character.h
 * \brief header de character.c
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "const.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "file_level.h"
#include "share.h"
#include "map.h"

#include "structures.h"
#include "image.h"
#include "enemies.h"
#include "mobile_platform.h"
#include "sound.h"


//#include "character_list.h"

/**
 *\def SGN(X)
 *X sign
 */
#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))

/**
 *\def ABS(X)
 *X absolute value
 */
#define ABS(X) ((((X)<0)?(-(X)):(X)))


/**
 *\fn int moveCharacter(Character *c,int move_left, int move_right,int jump,Map *m,float *speed,list *l, Sound *sound_sys,platformSet *ps)
 *move player according to the direction
 *\param[in,out] c the character
 *\param[in] move_left indicates if must go to the left
 *\param[in] move_right indicates if must go to the right
 *\param[in] jump indicates if must jump
 *\param[in] m level map
 *\param[in] speed movement speed
 *\param[in,out] l the enemy list
 *\param[out] sound_sys the sound system
 *\return 1 if character was moved without using the precise movement function, 0 if not
 */
int moveCharacter(Character *c,float move_left, float move_right,int jump,Map *m,float* speed,list *l,Sound *s,platformSet *ps);

/**
 *\fn void freeCharacters(Character *c)
 * Free a character
 *\param[in,out] c the character
 */
void freeCharacters(Character *c);

/**
 *\fn Character *createCharacter(char *tile,int x, int y,int npc, int nbProjectile, int nbCoins, int nbLifes)
 *create a character
 *\param[in] tile character tileSet address
 *\param[in] x character's x location
 *\param[in] y character's y location
 *\param[in] npc type of npc if creating a npc, 0 if not
 *\param[in] nbProjectile the number of projectiles the character has
 *\param[in] nbCoins the number of coins the character has
 *\param[in] nbLifes the number of life the character has
 *\return character structure pointer
 */
Character *createCharacter(char *tile,int x, int y,int npc, int nbProjectile, int nbCoins, int nbLifes);

/**
 *\fn void blitCharacter(SDL_Surface *screen, Character *c, Map *m)
 *blit the character
 *\param[in,out] screen game screen
 *\param[in] c the character
 *\param[in] m game map
 */
void blitCharacter(SDL_Surface *screen, Character *c,Map *m);


/**
 *\fn int tryMovement(Character *c,int vx,in vy,Map *m,list *l,platformSet *ps,Sound *sound_sys)
 *try to move a character
 *\param[in,out] c the character
 *\param[in] vx the horizontal component of the movement vector
 *\param[in] vy the vertical component of the movement vector
 *\param[in] m the map the character is on
 *\param[in,out] l the enemy list
 *\param[out] ps the platform set
 *\param[out] sound_sys the game sound system
 *\return 1 if the character can be moved, 0 if not
 */
int tryMovement(Character *c,int vx,int vy,Map *m,list *l,platformSet *ps,Sound *sound_sys);

/**
 *\fn void presiseMoveCharacter(Charactere *c, int vx,int vy, Map *m,list *l,platformSet *ps)
 *make a more presise move of a character if he can still move but the distance between it and the obstacle is less than its speed
 *\param[in,out] c the charactere
 *\param[in] m the map
 *\param[in] vx the horizontal component of the movement vector
 *\param[in] vy the vertical component of the movement vector
 *\param[in,out] l the enemy list
 *\param[out] ps the platform set
 */
void presiseMoveCharacter(Character *c, int vx,int vy, Map *m,list *l,platformSet *ps);

/**
 *int collisionSprite(SDL_Rect s1, SDL_Rect s2)
 *determine if there is a collision beteewen two sprites
 *\param[in] s1 the first sprite
 *\param[in] s2 the second sprite
 *\return 3 if there is a collision and s1 is below s2, 2 if there is a collision and s1 is over s2, 0 if there is no collision
*/
int collisionSprite(SDL_Rect s1, SDL_Rect s2);

/**
 *\fn int checkFall(Character *c,Map *m,platformSet *ps)
 *tests if the character's futur position is over a void tile
 *\param[in] c the monster/character to be tested
 *\param[in] m the game map
 *\param[in] ps the platform set
 *\return 1 if void tile, 0 if not
 */
int checkFall(Character *c,Map *m,platformSet *ps);

 /**
 *\fn int checkWall(Character *c,Map *m)
 *tests if the character's futur position is next to a wall tile
 *\param[in] c the monster/character to be tested
 *\param[in] m the game map
 *\return 1 if wall tile, 0 if not
 */
int checkWall(Character *c,Map *m);




#endif
