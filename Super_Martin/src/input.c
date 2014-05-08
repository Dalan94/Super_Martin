/*!
 *\file input.c
 *\brief the funtions to deal with the player inputs
 *\author Xavier COPONET
 *\date 2014-03-18
 */

#include "input.h"
#include "SDL/SDL_joystick.h"
#include "projectile.h"

/**
 *\fn void initInput(Input *in)
 * initialize the input structure
 *\param[out] in the input structure to be initialized
 */
void initInput(Input *in)
{
    int i;

    for(i = 0; i<SDLK_LAST ; i++)
        in->key[i] = 0;

    in->quit = 0;

    initJoystick(in);
}

/**
 *\fn void initJoystick(Joystick *joy)
 * initialize the joystic fiels of the input structure
 *\param[out] joy the joystick input structure to be initialized
 */
void initJoystick(Input *in)
{
    int i;
    int ret;

    in->hatMoved = 0;
    if(!SDL_NumJoysticks())
    {
        in->isJoystick = 0;
        SDL_JoystickEventState(SDL_IGNORE);
        return ;
    }

    in->joystick = SDL_JoystickOpen(0);
    if(in->joystick == NULL )
    {
        perror("error while opening the joystick");
        exit(errno);
    }
    if(strcmp("Microsoft X-Box 360 pad",SDL_JoystickName(0)))
    {
        in->isJoystick = 0;
        SDL_JoystickEventState(SDL_IGNORE);
        return;
    }


    in->isJoystick = 1;
    ret = SDL_JoystickNumAxes(in->joystick);
    in->axes = (int *)malloc(sizeof(int)*ret);
    if(in->axes == NULL)
    {
        perror("allocation error");
        exit(errno);
    }
    for(i = 0; i<ret ; i++)
        in->axes[i] = 0;

    ret = SDL_JoystickNumButtons(in->joystick);
    in->button = (char *)malloc(sizeof(char)*ret);
    if(in->button == NULL)
    {
        perror("allocation error");
        exit(errno);
    }
    for(i = 0; i<ret ; i++)
        in->button[i] = 0;

    ret = SDL_JoystickNumHats(in->joystick);
    in->hat = (int *)malloc(sizeof(char)*ret);
    if(in->hat == NULL)
    {
        perror("allocation error");
        exit(errno);
    }
    for(i = 0; i<ret ; i++)
        in->hat[i] = SDL_HAT_CENTERED;

}

/**
 *\fn void freeInput(Input *in)
 * free the input structure
 *\param[out] in the input structure
 */
void freeInput(Input *in)
{
    if(in->isJoystick)
    {
        free((void *)in->axes);
        free((void *)in->button);
        free((void *)in->hat);
        SDL_JoystickClose(in->joystick);
    }
}

/**
 *\fn int updateEvents(Input* in)
 *recuperate keyboard/joystick input with a SDL_PollEvent
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

		/* **** Keyboard **** */
		case SDL_KEYDOWN:
			in->key[event.key.keysym.sym] = 1;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.sym] = 0;
			break;

        /* **** Joystick **** */
            /* buttons */
        case SDL_JOYBUTTONDOWN:
            in->button[event.jbutton.button] = 1;
            break;
        case SDL_JOYBUTTONUP:
            in->button[event.jbutton.button] = 0;
            break;

            /* axes */
        case SDL_JOYAXISMOTION:
            in->axes[event.jaxis.axis] = event.jaxis.value;
            break;

            /* hats */
        case SDL_JOYHATMOTION:
            in->hat[event.jhat.hat] = event.jhat.value;
            break;


        /* ****************** */
        case SDL_QUIT:
            in->quit = 1;
            *go = 0;
            break;
		default:
            return 0;
			break;
		}
	}
	return 1;
}


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
void inputActionGame(Input *in,float *move_left,float *move_right,int *jump,int *pause, Character *player, int *acceleration, SDLKey *kc,projectileSet *ps)
{
    /*left move*/
    if((in->key[kc[L]] || in->isJoystick&&(in->hat[0] == SDL_HAT_LEFT))
            && (player->dirY < (-JUMP_HEIGHT + 7) || (player->doubleJump == 0 && player->isOnGround)))
        *move_left = 1;
    if(!(in->key[kc[L]] || in->isJoystick&&(in->hat[0]==SDL_HAT_LEFT && in->axes[0]>-3000)) && player->isOnGround)
        *move_left = 0;
    if(in->isJoystick&&(in->axes[0] < - 3000))
    {
        *move_left = ABS(in->axes[0])*MAX_SPEED/32000;
    }

    /*right move*/
    if((in->key[kc[R]] || in->isJoystick&&(in->hat[0] == SDL_HAT_RIGHT))
            && (player->dirY < (-JUMP_HEIGHT + 7) || (player->doubleJump == 0 && player->isOnGround)))
        *move_right = 1;
    if(!(in->key[kc[R]] || in->isJoystick&&(in->hat[0]==SDL_HAT_RIGHT && in->axes[0]<3000)) && player->isOnGround)
        *move_right = 0;
    if(in->isJoystick&&in->axes[0] > 3000)
    {
        *move_right = ABS(in->axes[0])*MAX_SPEED/32000;
    }
    /*jump*/
    if(in->key[kc[J]] || in->isJoystick&&in->button[A])
    {
         *jump = 1;
    }

    if((!in->key[kc[J]] && !in->isJoystick|!in->button[A]) && *(jump)==1)
    {
        *jump = 2;
        if(!player->doubleJump)
            player->doubleJump = 1;
    }
    else if((!in->key[kc[J]] && !in->isJoystick|!in->button[A]) && (*jump==2 || *jump==0))
        *jump = 0;

        /*pause*/
    if(in->key[kc[3]] || in->isJoystick&&in->button[START])
        *pause = 1;

        /*acceleration*/
    if ((!in->key[kc[R]] && !in->key[kc[L]]
        &&  in->isJoystick&&(in->hat[0] == SDL_HAT_CENTERED)) && player->isOnGround)
        *acceleration = 0;

        /* projectiles */
    if((in->key[kc[H]] || in->isJoystick&&in->button[X]) && player->nbProjectile > 0)
    {
        if(!ps->projectileThrown)
        {
            if(player->isRight)
                createProjectile(ps,RIGHT,player->location.x+player->location.w+1,player->location.y+player->location.h/2-11);
            else
                createProjectile(ps,LEFT,player->location.x-1,player->location.y+player->location.h/2-11);

            ps->projectileThrown = 1;
            if(--player->nbProjectile <= 0)
                player->nbProjectile = 0;
        }
    }
    else
        ps->projectileThrown = 0;
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
	//SDL_EnableKeyRepeat(100,100);
    if(in->isJoystick && in->hatMoved)
    {
        while (SDL_PollEvent (&event));
        in->hatMoved = 0;
    }
	SDL_WaitEvent(&event);

    switch (event.type)
    {
        /* **** Keyboard **** */
		case SDL_KEYDOWN:
			in->key[event.key.keysym.sym] = 1;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.sym] = 0;
            return 0;
			break;

        /* **** Joystick **** */
            /* buttons */
        case SDL_JOYBUTTONDOWN:
            in->button[event.jbutton.button] = 1;
            break;
        case SDL_JOYBUTTONUP:
            in->button[event.jbutton.button] = 0;
            return 0;
            break;

            /* axes */
        case SDL_JOYAXISMOTION:
            in->axes[event.jaxis.axis] = event.jaxis.value;
            break;

            /* hats */
        case SDL_JOYHATMOTION:
            in->hat[event.jhat.hat] = event.jhat.value;
            in->hatMoved = 1;
            break;

        /* ****************** */
        case SDL_QUIT:
            in->quit = 1;
            *go = 0;
            break;
		default:
            return 0;
			break;

    }
	return 1;
}

/**
 *\fn void inputActionMenu(Input *in,int *cursorPos,int *play_level,int nb_lvl)
 *perform action command by keyboard action
 *\param[in] in the input structure
 *\param[out] cursorPos cursor position
 *\param[out] play_level boolean about playing the level or quit to title screen
 *\param[in] nb_lvl the number of levels

 */
void inputActionMenu(Input *in,int *cursorPos,int *play_level,int nb_lvl)
{
    if((in->key[SDLK_ESCAPE] || in->quit || in->isJoystick&in->button[BACK]) && play_level != NULL)
        (*play_level) = 0;

    if(in->key[SDLK_UP] || in->isJoystick&&(in->hat[0] == SDL_HAT_UP))
    {
        (*cursorPos)--;
        if(*cursorPos < 0)
            (*cursorPos) = nb_lvl-1;
        //SDL_Delay(100);
    }
    if(in->key[SDLK_DOWN] || in->isJoystick&&(in->hat[0] == SDL_HAT_DOWN))
    {
        (*cursorPos)++;
        if(*cursorPos >= nb_lvl)
            (*cursorPos) = 0;
       // SDL_Delay(100);
    }
}
