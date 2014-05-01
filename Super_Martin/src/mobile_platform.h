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

#endif // MOBILE_PLATFORM_H_INCLUDED
