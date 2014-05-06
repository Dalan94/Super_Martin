#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "SDL/SDL_joystick.h"
#include "character.h"

/**
 *\struct Joystick
 *joystick input structure
 */
//typedef struct
//{
//
//    char *button; /*! all the joystick buttons : 1 the button is pushed, 0 isn't */
//    int *axes; /*! the axes value : between -32768 and 32767 */
//    int *hat; /*! the hats value : SDL_HAT_CENTERED, SDL_HAT_UP, SDL_HAT_RIGHT,
//                SDL_HAT_DOWN, SDL_HAT_LEFT, SDL_HAT_RIGHTUP, SDL_HAT_RIGHTDOWN, SDL_HAT_LEFTUP, SDL_HAT_LEFTDOWN*/
//}Joystick;

/**
 *\struct Input
 *the global input structure
 */
typedef struct
{
	char key[SDLK_LAST]; /*! all the keyboard keys : 1 the key is pushed, 0 isn't */
	int quit; /*! is 1 is the SDL_QUIT event happens */

    int isJoystick;
	SDL_Joystick *joystick; /*! the joystick */
	char *button; /*! all the joystick buttons : 1 the button is pushed, 0 isn't */
    int *axes; /*! the joystick axes value : between -32768 and 32767 */
    int *hat; /*! the  joystick hats value : SDL_HAT_CENTERED, SDL_HAT_UP, SDL_HAT_RIGHT,
                SDL_HAT_DOWN, SDL_HAT_LEFT, SDL_HAT_RIGHTUP, SDL_HAT_RIGHTDOWN, SDL_HAT_LEFTUP, SDL_HAT_LEFTDOWN*/

} Input;

/*prototype*/
void initInput(Input *in);
void initJoystick(Input *in);
void freeInput(Input *in);
int updateEvents(Input* in,int *go);
void inputActionGame(Input *in,int *move_left,int *move_right,int *jump,int *pause,Character *player,int *acceleration,SDLKey *kc);
int updateWaitEvents(Input* in,int *go);
void keyboardActionMenu(Input *in,int *cursorPos,int *play_level,int nb_lvl);

#endif // INPUT_H_INCLUDED
