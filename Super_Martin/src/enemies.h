/*!
 * \file enemies.h
 * \brief  enemies.c header
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef ENEMIES_H_INCLUDED
#define ENEMIES_H_INCLUDED

#include "character_list.h"

void createEnemy(char *spR,char *spL,int x,int y, list *l);
void blitEnnemies(SDL_Surface *screen, list *l,Map *m);

#endif // ENEMIES_H_INCLUDED
