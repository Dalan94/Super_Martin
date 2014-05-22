/*!
 * \file text.h
 * \brief text.c header
 * \author Xavier COPONET, Glenn HERROU
 * \date 2014-04-27
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

/**
 *\fn void printText(SDL_Surface *screen, SDL_Rect *posText, char *text, int r,int g, int b, char *font,int ptSize,int mode)
 *Display the given text on the screen, at the given position
 *\param[out] screen The screen of the game
 *\param[in] posText The position of the text. If NULL, the text is centered
 *\param[in] text The text to display
 *\param[in] int r red value
 *\param[in] int g green value
 *\param[in] int b blue value
 *\param[in] font The path to the font file
 *\param[in] ptSize The text size
 *\param[in] mode The writing mode : 0 (Solid), 1 (Blended)
 */

void printText(SDL_Surface *screen, SDL_Rect *posText, char *text, int r,int g, int b, char *font,int ptSize,int mode);

/**
 *\fn void captureText(SDL_Surface *screen, SDL_Rect posText,char *text, int text_length, int r, int g, int b, char *font, int text_size,  int *go)
 *Capture the text corresponding to the keyboard inputs and display it on the screen at the given position
 *\param[out] screen The screen of the game
 *\param[in] posText The position of the text. If NULL, the text is centered
 *\param[out] text The text to display
 *\param[in] int r red value
 *\param[in] int g green value
 *\param[in] int b blue value
 *\param[in] font The path to the font file
 *\param[in] ptSize The text size
 *\param[in] mode The writing mode : 0 (Solid), 1 (Blended)
 *\param[out] go The main loop validation
 */

void captureText(SDL_Surface *screen, SDL_Rect posText,char *text, int text_length, int r, int g, int b, char *font, int text_size, int *go);


#endif // TEXT_H
