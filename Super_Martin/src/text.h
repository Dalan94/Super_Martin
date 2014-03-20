/*!
 * \file text.h
 * \brief header de text.c
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef TEXT_H
#define TEXT_H


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


void printText(SDL_Surface *screen, SDL_Rect *posText, char *text, int r,int g, int b, char *font,int ptSize,int mode);


#endif // TEXT_H
