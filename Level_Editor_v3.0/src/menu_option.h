/**
 *\file menu_option.h
 *\brief menu_option.c header
 *\author Xavier COPONET
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
#include "share.h"
#include "image.h"
#include "input.h"
#include "option.h"

/**
 *\fn int menuOptions(SDL_Surface *screen,int *go,SDLKey *kc)
 *print the option menu on the screen
 *\param[out] screen the game screen
 *\param[in,out] go main loop validation
 *\param[in,out] kc the keyboard configuration
 *\return the number of the option which is choosen, -1 if esc
 */

int menuOptions(SDL_Surface *screen,int *go, SDLKey *kc);

/**
 *\fn void keyboardOptions(SDL_Surface *screen,int *go,SDLKey *kc)
 *print the keyboard options and deals with the user choises
 *\param[out] screen the game screen
 *\param[in,out] go main loop validation
 *\param[in,out] kc the keyboard config
 */

void keyBoardOptions(SDL_Surface *screen,int *go,SDLKey *kc);

/**
 *\fn void chooseKey(SDL_Surface *screen,Input *in,char *action,SDLKey *kc,int nb)
 *print the message asking the player to choose a key and wait until the player press a key and deals with this key
 *\param[out] screen the game screen
 *\param[in,out] in the input structure
 *\param[in] action the action which the key has to be choosen
 *\param[out] kc the keyboard configuration
 *\param[in] nb the number of the action
 */

void chooseKey(SDL_Surface *screen,Input *in,char *action,SDLKey *kc,int nb);

#endif // MENU_OPTION_H_INCLUDED
