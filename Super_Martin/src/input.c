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
void keyboardActionGame(Input *in,int *move_left,int *move_right,int *jump,int *pause, Character *player, int *acceleration, keyConf *kc)
{
    /*left move*/
    if(in->key[kc->left] && (player->dirY < (-JUMP_HEIGHT + 7) || (player->isJumping == 0 && player->isOnGround)))
        *move_left = 1;
    if(!in->key[kc->left]  && player->isOnGround)
        *move_left = 0;

    /*right move*/
    if(in->key[kc->right] && (player->dirY < (-JUMP_HEIGHT + 7) || (player->isJumping == 0 && player->isOnGround)))
        *move_right = 1;
    if(!in->key[kc->right] && player->isOnGround)
        *move_right = 0;

    /*jump*/
    if(in->key[kc->jump] && player->isOnGround)
        *jump = 1;
    if(!in->key[kc->jump] && *(jump)==1)
        *jump = 2;
    else if(!in->key[kc->jump] && (*jump==2 || *jump==0))
        *jump = 0;

        /*pause*/
    if(in->key[kc->pause])
        *pause = 1;

    if (!in->key[kc->right] && !in->key[kc->left] && player->isOnGround)
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
 *\fn void keyboardActionMenu(Input *in,int *cursorPos,int *play_level,int nb_lvl)
 *perform action command by keyboard action
 *\param[in] in the input structure
 *\param[out] cursorPos cursor position
 *\param[out] play_level boolean about playing the level or quit to title screen
 *\param[in] nb_lvl the number of levels

 */
void keyboardActionMenu(Input *in,int *cursorPos,int *play_level,int nb_lvl)
{
    if((in->key[SDLK_ESCAPE] || in->quit) && play_level != NULL)
        (*play_level) = 0;

    if(in->key[SDLK_UP])
    {
        (*cursorPos)--;
        if(*cursorPos < 0)
            (*cursorPos) = nb_lvl-1;
    }
    if(in->key[SDLK_DOWN])
    {
        (*cursorPos)++;
        if(*cursorPos >= nb_lvl)
            (*cursorPos) = 0;
    }
}
