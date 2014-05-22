#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "const.h"
#include "structures.h"
#include "map.h"

/**
 *\fn void updateEvents(Input* in)
 *get keyboard input with a SDL_PollEvent
 *\param[out] in the input structure
 */

void updateEvents(Input* in);

/**
 *\fn void keyboardActionGame(SDL_Surface *screen, Input *in, Map *m, Cursor *cursor, SDLKey *kc)
 *perform action commanded by keyboard action
 *\param[in,out] screen The screen of the game
 *\param[in,out] in the input structure
 *\param[in,out] m the map to update
 *\param[in,out] cursor the cursor structure
 *\param[in] kc the keyboard bindings
 */

void keyboardActionGame(SDL_Surface *screen, Input *in, Map *m, Cursor *cursor, SDLKey *kc);

/**
 *\fn int updateWaitEvents(Input* in)
 *get keyboard input with a SDL_WaitEvent
 *\param[out] in the input structure
 *\return 1 if a key is activated
 */

int updateWaitEvents(Input* in);

/**
 *\fn void keyboardActionMenu(Input *in,int *cursorPos,int *select,int nb_options)
 *perform  menu action commanded by keyboard action
 *\param[in] in the input structure
 *\param[out] cursorPos the cursor position
 *\param[out] select boolean about selecting the option or quit to title screen
 *\param[in] nb_options the number of options of the menu
 */

int keyboardActionMenu(Input *in,int *cursorPos,int *select,int nb_options);

#endif // INPUT_H_INCLUDED
