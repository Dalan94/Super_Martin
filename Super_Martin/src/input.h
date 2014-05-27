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
    A = 0,B,X,Y,R1=5,BACK = 6,START
}joyButton;

/**
 *\struct Input
 *the global input structure
 */
typedef struct
{
	char key[SDLK_LAST]; /*!< all the keyboard keys : 1 the key is pushed, 0 isn't */
	int space; /*!< Space */

	int quit; /*!< is 1 is the SDL_QUIT event happens */

    int isJoystick; /*!< indicate if there is a joystick plugged in */
    int useJoystick; /*!< indicate if the joystick is willing to be used */
	SDL_Joystick *joystick; /*!< the joystick */
	char *button; /*!< all the joystick buttons : 1 the button is pushed, 0 isn't */
    int *axes; /*!< the joystick axes value : between -32768 and 32767 */
    int *hat; /*!< the  joystick hats value : SDL_HAT_CENTERED, SDL_HAT_UP, SDL_HAT_RIGHT,
                SDL_HAT_DOWN, SDL_HAT_LEFT, SDL_HAT_RIGHTUP, SDL_HAT_RIGHTDOWN, SDL_HAT_LEFTUP, SDL_HAT_LEFTDOWN*/
    int hatMoved; /*!< indicates if a hat has been moved during the last updateEvent */

} Input;

/*prototype*/

/**
 *\fn void initInput(Input *in)
 * initialize the input structure
 *\param[out] in the input structure to be initialized
 */
void initInput(Input *in);

/**
 *\fn void initJoystick(Input *in)
 * initialize the joystic fiels of the input structure
 *\param[out] in the joystick input structure to be initialized
 */
void initJoystick(Input *in);

/**
 *\fn void freeInput(Input *in)
 * free the input structure
 *\param[out] in the input structure
 */
void freeInput(Input *in);

/**
 *\fn int updateEvents(Input* in,int *go);
 *recuperate keyboard/joystick input with a SDL_PollEvent
 *\param[out] in the input structure
 *\param[out] go the software main loop validation
 *\return 1 if a key is activated
 */
int updateEvents(Input* in,int *go);

/**
 *\fn void inputActionGame(Input *in,float *move_left,float *move_right,int *jump,int *pause, Character *player, int *acceleration,SDLKey *kc,projectileSet *ps)
 *perform action command by keyboard or joystick action
 *\param[in] in the input structure
 *\param[out] move_left the left movement boolean
 *\param[out] move_right the right movement boolean
 *\param[out] jump the jump boolean
 *\param[out] pause the pause boolean
 *\param[in] player the Player
 *\param[in] acceleration the acceleration
 *\param[in] kc the keyboard configuration structure
 *\param[out] ps the projectile set
 */
void inputActionGame(Input *in,float *move_left,float *move_right,int *jump,int *pause,Character *player,int *acceleration,SDLKey *kc,projectileSet *ps);

/**
 *\fn int updateWaitEvents(Input* in, int *go)
 *recuperate keyboard input with a SDL_WaitEvent
 *\param[out] in the input structure
 *\param[in,out] go the software main loop validation
 *\return 1 if a key is activated
 */
int updateWaitEvents(Input* in,int *go);

/**
 *\fn void inputActionMenu(Input *in,int *cursorPos,int *play_level,int nb_lvl)
 *perform action command by keyboard action
 *\param[in] in the input structure
 *\param[out] cursorPos cursor position
 *\param[out] play_level play level
 *\param[in] nb_lvl the number of level
 */
void inputActionMenu(Input *in,int *cursorPos,int *play_level,int nb_lvl);

#endif // INPUT_H_INCLUDED
