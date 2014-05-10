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




/*prototypes*/

int moveCharacter(Character *c,float move_left, float move_right,int jump,Map *m,float* speed,list *l,Sound *s,platformSet *ps);
Character *createCharacter(char *tile,int x, int y,int npc, int nbProjectile, int nbCoins, int nbLifes);

void blitCharacter(SDL_Surface *screen, Character *c,Map *m);

void gravity(Character *c, Map *m,list *l);
void movementVector(int direction, int *vx, int *vy,float speed);
int tryMovement(Character *c,int vx,int vy,Map *m,list *l,platformSet *ps,Sound *sound_sys);
void presiseMoveCharacter(Character *c, int vx,int vy, Map *m,list *l,platformSet *ps);
void jumping(Character *c, Map *m,Sound *jump_sound,list *l);
int collisionSprite(SDL_Rect s1, SDL_Rect s2);
int checkFall(Character *c,Map *m,platformSet *ps);
int checkWall(Character *c,Map *m);




#endif
