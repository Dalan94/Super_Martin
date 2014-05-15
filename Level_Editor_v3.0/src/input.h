#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "const.h"
#include "structures.h"
#include "map.h"

void updateEvents(Input* in);
void keyboardActionGame(SDL_Surface *screen, Input *in, Map *m, Cursor *cursor, SDLKey *kc);
int updateWaitEvents(Input* in);
int keyboardActionMenu(Input *in,int *cursorPos,int *select,int nb_options);

#endif // INPUT_H_INCLUDED
