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
#include "jeu.h"

typedef struct{
    SDL_Surface *spriteR,*spriteL;
    SDL_Rect location;
}Character;

/*prototypes*/
Character *createrCharacter(char *spR,char *spL);

#endif
