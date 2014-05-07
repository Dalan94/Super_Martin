#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "character.h"

/**
 *\enum joyButton
 *the joystick's button
 */
typedef enum
{
    A = 0,B,X,Y,BACK = 6,START,
}joyButton;

/**
 *\struct Input
 *the global input structure
 */
typedef struct
{
	char key[SDLK_LAST]; /*! all the keyboard keys : 1 the key is pushed, 0 isn't */
	int quit; /*! is 1 is the SDL_QUIT event happens */

    int isJoystick; /*! indicate if there is a joystick plugged in */
    int useJoystick; /*! indicate if the joystick is willing to be used */
	SDL_Joystick *joystick; /*! the joystick */
	char *button; /*! all the joystick buttons : 1 the button is pushed, 0 isn't */
    int *axes; /*! the joystick axes value : between -32768 and 32767 */
    int *hat; /*! the  joystick hats value : SDL_HAT_CENTERED, SDL_HAT_UP, SDL_HAT_RIGHT,
                SDL_HAT_DOWN, SDL_HAT_LEFT, SDL_HAT_RIGHTUP, SDL_HAT_RIGHTDOWN, SDL_HAT_LEFTUP, SDL_HAT_LEFTDOWN*/
    int hatMoved; /*! indicates if a hat has been moved during the last updateEvent */

} Input;

/*prototype*/
void initInput(Input *in);
void initJoystick(Input *in);
void freeInput(Input *in);
int updateEvents(Input* in,int *go);
void inputActionGame(Input *in,float *move_left,float *move_right,int *jump,int *pause,Character *player,int *acceleration,SDLKey *kc);
int updateWaitEvents(Input* in,int *go);
void inputActionMenu(Input *in,int *cursorPos,int *play_level,int nb_lvl);

#endif // INPUT_H_INCLUDED
