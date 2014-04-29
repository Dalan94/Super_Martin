/**
 *\file menu_option.h
 *menu_option.h
 *\author X.COPONET
 *\date 2014-04-27
 */

#ifndef MENU_OPTION_H_INCLUDED
#define MENU_OPTION_H_INCLUDED


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


#include "const.h"
#include "text.h"
#include "sound.h"
#include "share.h"
#include "image.h"
#include "input.h"
#include "option.h"

int optionMenu(SDL_Surface *screen,int *go,Sound *sound_sys,keyConf *kc);
void soundOptions(SDL_Surface *screen,int *go,Sound *sound_sys);

#endif // MENU_OPTION_H_INCLUDED
