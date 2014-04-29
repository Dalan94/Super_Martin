#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "character.h"



typedef struct
{
	char key[SDLK_LAST];
	int quit;
} Input;

/*prototype*/
int updateEvents(Input* in,int *go);
void keyboardActionGame(Input *in,int *move_left,int *move_right,int *jump,int *pause,Character *player,int *acceleration,keyConf *kc);
int updateWaitEvents(Input* in,int *go);
void keyboardActionMenu(Input *in,int *cursorPos,int *play_level,int nb_lvl);

#endif // INPUT_H_INCLUDED
