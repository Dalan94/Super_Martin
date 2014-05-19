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
#include "structures.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "input.h"


void printText(SDL_Surface *screen, SDL_Rect *posText, char *text, int r,int g, int b, char *font,int ptSize,int mode);
void captureText(SDL_Surface *screen, SDL_Rect posText,char *text, int text_length, int r, int g, int b, char *font, int text_size, int *go);


#endif // TEXT_H
