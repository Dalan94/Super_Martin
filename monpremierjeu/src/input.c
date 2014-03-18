/*!
 *\file input.c
 *\brief
 *\author Xavier COPONET
 *\date 2014-03-18
 */

#include "input.h"


/**
 *\fn int updateEvents(Input* in)
 *recuperate keyboard input
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
 *\fn void keyboardAction(Input *in,int *move_left,int *move_right,int *jump,int *pause, Character *player)
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
