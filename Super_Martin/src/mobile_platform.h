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

void initPlatformSet(platformSet *ps);
void createPlatform(platformSet *ps,int x1,int y1,int x2, int y2);
void blitPlatform(SDL_Surface *screen, platformSet *ps, Map *m);
void movePlatform(Character *c,platformSet *ps,list *l);
void moveOnePlatform(Character *c,platform *p,list *l,int nb);
int collisionPlatform(Character *c,platformSet *ps,SDL_Rect futureLocation);
void freePlatformSet(platformSet *ps);

void platformMap(platformSet *ps, SDL_Rect array[],SDL_Rect mark,int vert);

#endif // MOBILE_PLATFORM_H_INCLUDED
