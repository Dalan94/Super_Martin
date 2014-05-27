/*!
 * \file image.h
 * \brief contient les fonction liées aux images
 * \author Rémi BERTHO
 * \date 2014-02-27
 */

#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "const.h"

/**
 *\fn SDL_Surface *imageLoad(char * file_name)
 * Load an image
 *\param[in] file_name the name of the image file
 *\return a pointer on the SDL_Surface created
 */

SDL_Surface *imageLoad(char * file_name);

/**
 *\fn SDL_Surface *imageLoadAlpha(char * file_name)
 * Load an image with alpha management
 *\param[in] file_name the name of the image file
 *\return a pointer on the SDL_Surface created
 */
SDL_Surface *imageLoadAlpha(char * file_name);

/**
 *\fn void blitColor(Uint32 red, Uint32 green,Uint32 blue, int alpha,SDL_Surface *screen);
 * Blit a color on the screen
 *\param[in] red the red of the color
 *\param[in] green the green of the color
 *\param[in] blue the blue of the color
 *\param[in] alpha the transparency of the image file
 *\param[in] screen the screen
 */
void blitColor(Uint32 red, Uint32 green,Uint32 blue, int alpha,SDL_Surface *screen);

#endif // IMAGE_H_INCLUDED

