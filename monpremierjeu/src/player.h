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


typedef struct{
    SDL_Surface *spriteR,*spriteL;
    SDL_Rect location;
    int isRight; /*! indique la direction de regard du personnage (1 droite, 0 gauche)*/
}Character;

/*prototypes*/
Character *createrCharacter(char *spR,char *spL);
void moveCharacter(Character *c,int direction, Map *m,float speed);
void blitCharacter(SDL_Surface *screen, Character *c,Map *m);
int collisionSprite(SDL_Rect r,Map *m);

#endif
