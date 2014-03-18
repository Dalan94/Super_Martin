/*!
 * \file player.h
 * \brief header de player.c
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
#include "image.h"

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

typedef struct{
    SDL_Surface *spriteR,*spriteL;
    SDL_Rect location;
    int isRight; /*! indique la direction de regard du personnage (1 droite, 0 gauche)*/
    int isOnGround; /*! indique si le perso est au sol*/
    int isJumping; /*! 0 when not, height remaning between character and max height if jumping*/
}Character;



/*prototypes*/
Character *createrCharacter(char *spR,char *spL);
int moveCharacter(Character *c,int direction, Map *m,float speed);
void blitCharacter(SDL_Surface *screen, Character *c,Map *m);
int collisionSprite(SDL_Rect r,Map *m);
void gravity(Character *c, Map *m,SDL_Surface *screen);
void movementVector(int direction, int *vx, int *vy,int speed,Character *c);
int tryMovement(Character *c,int vx,int vy,Map *m);
void presiseMoveCharacter(Character *c, int vx,int vy, Map *m);
void jumping(Character *c, Map *m);

#endif
