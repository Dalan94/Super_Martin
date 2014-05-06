/*!
 *\file input.c
 *\brief
 *\author Xavier COPONET
 *\date 2014-03-18
 */

#include "input.h"


/**
 *\fn int updateEvents(Input* in)
 *recuperate keyboard input with a SDL_PollEvent
 *\param[out] in the input structure
 *\return 1 if a key is activated
 */

int updateEvents(Input* in,int *go)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			in->key[event.key.keysym.sym] = 1;
			return 1;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.sym] = 0;
			break;
        case SDL_QUIT:
            in->quit = 1;
            *go = 0;
            break;
		default:
			break;
		}
	}
	return 0;
}


/**
 *\fn void keyboardActionGame(Input *in,int *move_left,int *move_right,int *jump,int *pause, Character *player, int *acceleration,keyConf *kc)
 *perform action command by keyboard action
 *\param[in] in the input structure
 *\param[out] move_left the left movement boolean
 *\param[out] move_right the right movement boolean
 *\param[out] jump the jump boolean
 *\param[out] pause the pause boolean
 *\param[in] player the Player
 *\param[in] acceleration the acceleration
 *\param[in] kc the keyboard configuration structure
 */
void keyboardActionGame(Input *in,int *move_left,int *move_right,int *jump,int *pause, Character *player, int *acceleration, SDLKey *kc)
{
    /*left move*/
    if(in->key[kc[0]] && (player->dirY < (-JUMP_HEIGHT + 7) || (player->doubleJump == 0 && player->isOnGround)))
        *move_left = 1;
    if(!in->key[kc[0]]  && player->isOnGround)
        *move_left = 0;

    /*right move*/
    if(in->key[kc[1]] && (player->dirY < (-JUMP_HEIGHT + 7) || (player->doubleJump == 0 && player->isOnGround)))
        *move_right = 1;
    if(!in->key[kc[1]] && player->isOnGround)
        *move_right = 0;

    /*jump*/
    if(in->key[kc[2]])
    {
         *jump = 1;
    }
    /*if(in->key[kc[2]] && player->isOnGround)
    {
        *jump = 1;
    }*/

    if(!in->key[kc[2]] && *(jump)==1)
    {
        *jump = 2;
        if(!player->doubleJump)
            player->doubleJump = 1;
    }
    else if(!in->key[kc[2]] && (*jump==2 || *jump==0))
        *jump = 0;

        /*pause*/
    if(in->key[kc[3]])
        *pause = 1;

    if (!in->key[kc[1]] && !in->key[kc[0]] && player->isOnGround)
        *acceleration = 0;
}


/**
 *\fn int updateWaitEvents(Input* in)
 *recuperate keyboard input with a SDL_WaitEvent
 *\param[out] in the input structure
 *\return 1 if a key is activated
 */

int updateWaitEvents(Input* in, int *go)
{
	SDL_Event event;
	SDL_EnableKeyRepeat(100,100);
	SDL_WaitEvent(&event);

    switch (event.type)
    {
		case SDL_KEYDOWN:
			in->key[event.key.keysym.sym] = 1;
			return 1;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.sym] = 0;
			break;
        case SDL_QUIT:
            in->quit = 1;
            *go = 0;
            return 1;
            break;
		default:
			break;
    }

	return 0;
}

/**
 *\fn void keyboardActionMenu(Input *in,int *cursorPos,int *select,int nb_options)
 *perform action command by keyboard action
 *\param[in] in the input structure
 *\param[out] cursorPos cursor position
 *\param[out] select boolean about selecting the current option
 *\param[in] nb_options the number of options

 */
void keyboardActionMenu(Input *in,int *cursorPos,int *select,int nb_options)
{
    if((in->key[SDLK_ESCAPE] || in->quit) && select != NULL)
        (*select) = 0;

    if(in->key[SDLK_UP])
    {
        (*cursorPos)--;
        if(*cursorPos < 0)
            (*cursorPos) = nb_options-1;
    }
    if(in->key[SDLK_DOWN])
    {
        (*cursorPos)++;
        if(*cursorPos >= nb_options)
            (*cursorPos) = 0;
    }
}
