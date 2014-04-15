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

#include "sound.h"

#include "image.h"



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

#include "structures.h"


/*prototypes*/
Character *createrCharacter(char *spR,char *spL,int x, int y,int x1,int x2);
int moveCharacter(Character *c,int move_left, int move_right,int jump,Map *m,float speed,list *l);
void blitCharacter(SDL_Surface *screen, Character *c,Map *m);
int collisionMap(SDL_Rect r,Map *m);
void gravity(Character *c, Map *m,list *l);
void movementVector(int direction,int speed,Character *c);
int tryMovement(Character *c,int vx,int vy,Map *m,list *l);
void presiseMoveCharacter(Character *c, int vx,int vy, Map *m,list *l);
void jumping(Character *c, Map *m,Sound *jump_sound,list *l);
int collisionSprite(SDL_Rect s1, SDL_Rect s2);

#endif
