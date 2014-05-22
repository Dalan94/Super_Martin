
/*!
 * \file game.h
 * \brief game.c header
 * \author Xavier COPONET, Glenn HERROU
 * \date 2014-05-15
 */

#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "const.h"
#include "structures.h"
#include "text.h"
#include "share.h"
#include "file_level.h"
#include "image.h"
#include "map.h"
#include "input.h"

/**
 *\fn void play(SDL_Surface *screen,char *level_name)
 *Include the main loop of the game
 *\param[in,out] screen The screen of the game
 *\param[in] level_name The name of the level
 *\param[in] kc The keyboard configuration
 */

void play(SDL_Surface *screen,char *level_name, SDLKey *kc);

/**
 *\fn void printConfirmation(SDL_Surface *screen, Input *in, int *go)
 * Display the confirmation screen, before leaving the edition of a level
 *\param[out] screen The screen of the game
 *\param[in] in The input structure
 *\param[out] go The main loop activation
 */

void printConfirmation(SDL_Surface *screen, Input *in, int *go);

#endif // JEU_H_INCLUDED
