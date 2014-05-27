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
#include "enemies.h"
#include <errno.h>

/* prototypes */
/**
 *\fn void initProjSet(projectileSet *projSet)
 *initialize a projectile set
 *\param[out] projSet the projectile set to be initialized
 */
void initProjSet(projectileSet *projSet);

/**
 *\fn void freeProjectileSet(projectileSet *ps)
 *free all the projectiles
 *\param[in,out] ps the projectile set
 */
void freeProjectileSet(projectileSet *ps);

/**
 *\fn void createProjectile(projectileSet *projSet, char *pathSprite,int dir, int x, int y, int fromNPC)
 *creates a projectile and adds it to the projectile set
 *\param[in,out] projSet the projectile set
 *\param[in,out] pathSprite the path for the sprite
 *\param[in] dir the projectile's direction
 *\param[in] x the start absciss coordinate of the projectile
 *\param[in] y the start ordinate coordinate of the projectile
 *\param[in] fromNPC indicates if from npc or not
*/
void createProjectile(projectileSet *projSet, char *pathSprite,int dir, int x, int y, int fromNPC);

/**
 *\fn void deleteProjectile(projectileSet *ps,int nb)
 *delete a projectile
 *\param[out] ps the projectile Set
 *\param[in] nb the number of the projectile which has to be deleted
 */
void deleteProjectile(projectileSet *ps,int nb);

/**
 *\fn void blitProjectile(SDL_Surface *screen, projectileSet *ps, Map *m)
 *blit the projectiles on the game screen
 *\param[in,out] screen game screen
 *\param[in,out] ps the projectile set
 *\param[in] m the current level map
 */
void blitProjectile(SDL_Surface *screen, projectileSet *ps, Map *m);

/**
 *\fn void moveProjectiles(Character *c,Map *m,projectileSet *ps,list *enemyList)
 *moves all the projectiles
 *\param[in,out] c the player
 *\param[in,out] m the game map
 *\param[in,out] ps the projectile set
 *\param[in,out] enemyList the enemy list
 */
void moveProjectiles(Character *c,Map *m,projectileSet *ps,list *enemyList);

/**
 *\fn void moveOneProjectile(Character *c,Map *m,projectileSet *ps,list *l,int nb)
 *moves one projectile
 *\param[in,out] c the player
 *\param[in,out] m the game map
 *\param[in,out] ps the projectileSet
 *\param[in,out] l the enemy list
 *\param[in] nb the number of the projectile which is moved
 */
void moveOneProjectile(Character *c,Map *m,projectileSet *ps,list *l,int nb);

#endif // PROJECTILE_H_INCLUDED
