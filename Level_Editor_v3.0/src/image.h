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

SDL_Surface *imageLoad(char * file_name);
SDL_Surface *imageLoadAlpha(char * file_name);

#endif // IMAGE_H_INCLUDED
