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

int updateEvents(Input* in)
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
		default:
			break;
		}
	}
	return 0;
}


/**
 *\fn void keyboardActionGame(Input *in,int *move_left,int *move_right,int *jump,int *pause, Character *player)
 *perform action command by keyboard action
 *\param[in] in the input structure
 *\param[out] move_left the left movement boolean
 *\param[out] move_right the right movement boolean
 *\param[out] jump the jump boolean
 *\param[out] pause the pause boolean
 *\param[in] player the Player

 */
void keyboardActionGame(Input *in,int *move_left,int *move_right,int *jump,int *pause, Character *player)
{
    /*left move*/
    if(in->key[SDLK_LEFT] && (player->isJumping > TAILLE_SAUT - 4 || (player->isJumping == 0 && player->isOnGround)))
        *move_left = 1;
    if(!in->key[SDLK_LEFT])
        *move_left = 0;

    /*right move*/
    if(in->key[SDLK_RIGHT] && (player->isJumping > TAILLE_SAUT - 4 || (player->isJumping == 0 && player->isOnGround)))
        *move_right = 1;
    if(!in->key[SDLK_RIGHT])
        *move_right = 0;

    /*jump*/
    if(in->key[SDLK_SPACE] && player->isOnGround)
        *jump = 1;
    if(!in->key[SDLK_SPACE])
        *jump = 0;

        /*pause*/
    if(in->key[SDLK_p])
        *pause = 1;
}


/**
 *\fn int updateWaitEvents(Input* in)
 *recuperate keyboard input with a SDL_WaitEvent
 *\param[out] in the input structure
 *\return 1 if a key is activated
 */

int updateWaitEvents(Input* in)
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
    if(in->key[SDLK_ESCAPE] || in->quit)
        (*play_level) = 0;

    if(in->key[SDLK_UP])
    {
        (*cursorPos)--;
        if(cursorPos < 0)
            (*cursorPos) = nb_lvl-1;
    }
    if(in->key[SDLK_DOWN])
    {
        (*cursorPos)++;
        if(*cursorPos >= nb_lvl)
            (*cursorPos) = 0;
    }
}
