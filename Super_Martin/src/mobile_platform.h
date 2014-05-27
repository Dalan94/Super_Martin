/**
 *\file mobile_platform.h
 *\brief mobile_platform.c header
 *\author X.COPONET
 *\date 2014-05-01
*/

#ifndef MOBILE_PLATFORM_H_INCLUDED
#define MOBILE_PLATFORM_H_INCLUDED

#include "structures.h"
#include "image.h"
#include "character.h"

/**
 *\fn void initPlatformSet(platformSet *ps)
 *initialize a platform set
 *\param[in] ps the platform set to be initialized
 */
void initPlatformSet(platformSet *ps);

/**
 *\fn void createPlatform(platformSet *ps,int x1,int y1,int x2, int y2)
 *creates of new platform and adds it to the platform set
 *\param[in,out] ps the platform set
 *\param[in] x1 the x low limit for deplacement
 *\param[in] x2 the x high limit for deplacement
 *\param[in] y1 the y low limit for deplacement
 *\param[in] y2 the y high limit for deplacement
 */
void createPlatform(platformSet *ps,int x1,int y1,int x2, int y2);

/**
 *\fn void blitPlatform(SDL_Surface *screen, platformSet *ps, Map *m)
 *blit the platforms on the game screen
 *\param[in,out] screen game screen
 *\param[in,out] ps the platform set
 *\param[in] m the current level map
 */
void blitPlatform(SDL_Surface *screen, platformSet *ps, Map *m);

/**
 *\fn void movePlatform(Character *c,platformSet *ps,list *l, Map *m)
 *moves all the platforms
 *\param[in,out] c the player
 *\param[in,out] ps the platform set
 *\param[in,out] l the enemy list
 *\param[in] m the game map
 */
void movePlatform(Character *c,platformSet *ps,list *l,Map *m);

/**
 *\fn void moveOnePlatform(Character *c,platform *p,list *l,int nb, Map *m)
 *moves one platforms
 *\param[in,out] c the player
 *\param[in,out] p the platform
 *\param[in,out] l the enemy list
 *\param[in] nb the number of the platform which is moved
 *\param[in] m the game map
 */
void moveOnePlatform(Character *c,platform *p,list *l,int nb,Map *m);

/**
 *\fn int collisionPlatform(Character *c,platformSet *ps, SDL_Rect futureLocation)
 *determine if there is a collision beteewen the player and a mobile platform and deals with
 *\param[in,out] c the player
 *\param[in,out] ps the platform set
 *\param[in] futureLocation the tryMovement variabla to test the future position
 *\return 1 if there is a collision, 0 if not
 */
int collisionPlatform(Character *c,platformSet *ps,SDL_Rect futureLocation);

/**
 *\fn void freePlatformSet(platformSet *ps)
 *free all the platforms
 *\param[in,out] ps the platform set
 */
void freePlatformSet(platformSet *ps);

/**
 *\fn void platformMap(platformSet *ps, SDL_Rect array[],SDL_Rect mark,int vert)
 *takes a limit mark for a vertical deplacement platform and creates a new platform if finds another
 *limit mark which match it, stocks it if doesn't find another limit mark
 *\param[out] ps the platform set
 *\param[in,out] array the array that stocks the limit marks
 *\param[in] mark the mark which has to be dealt with
 *\param[in] vert indicates if vertical movement(1) plarform or horizontal (0)
 */
void platformMap(platformSet *ps, SDL_Rect array[],SDL_Rect mark,int vert);

#endif // MOBILE_PLATFORM_H_INCLUDED
