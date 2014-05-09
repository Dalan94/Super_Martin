/**
 *\file projectile.h
 *\brief projectile.c header
 *\author X.COPONET
 *\date 2014-05-08
*/

#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include "structures.h"
#include "image.h"
#include <errno.h>

/* prototypes */
void initProjSet(projectileSet *projSet);
void freeProjectileSet(projectileSet *ps);
void createProjectile(projectileSet *projSet, int dir, int x, int y);
void deleteProjectile(projectileSet *ps,int nb);
void blitProjectile(SDL_Surface *screen, projectileSet *ps, Map *m);

void moveProjectiles(Map *m,projectileSet *ps,list *l);
void moveOneProjectile(Map *m,projectileSet *ps,list *enemyList,int nb);

#endif // PROJECTILE_H_INCLUDED
