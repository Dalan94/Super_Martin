#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "const.h"
#include "structures.h"

void updateEvents(Input* in);
void keyboardActionGame(Input *in, Map *m, Cursor *cursor);
int updateWaitEvents(Input* in);
void keyboardActionMenu(Input *in,int *cursorPos,int *select,int nb_options);

#endif // INPUT_H_INCLUDED
