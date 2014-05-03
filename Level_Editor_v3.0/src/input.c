/*!
 *\file input.c
 *\brief
 *\author Xavier COPONET, Glenn HERROU
 *\date 2014-03-18
 */

#include "input.h"


/**
 *\fn int updateEvents(Input* in)
 *recuperate keyboard input with a SDL_PollEvent
 *\param[out] in the input structure
 *\return 1 if a key is activated
 */

void updateEvents(Input* in)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
            case SDL_KEYDOWN:
                in->key[event.key.keysym.sym] = 1;
                printf(" keydown : %d\n", event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                if(((event.key.keysym.sym) != SDLK_y) && ((event.key.keysym.sym) != SDLK_n))
                {
                in->key[event.key.keysym.sym] = 0;
                }
                //printf(" keyup : %d\n", in->key[event.key.keysym.sym]);
                break;
            case SDL_MOUSEBUTTONDOWN :
                in->mouse[event.button.button] = 1;
                break;
            case SDL_MOUSEBUTTONUP :
                switch(event.button.button)
                {
                    case SDL_BUTTON_WHEELDOWN :
                        break;
                    case SDL_BUTTON_WHEELUP :
                        break;
                    default :
                        in->mouse[event.button.button] = 0;
                        break;
                }
                break;
            case SDL_QUIT:
                in->quit = 1;
            default:
                break;
		}
	}
	 /*  Record the coordinates of the mouse */

    SDL_GetMouseState(&in->mouseX, &in->mouseY);

    /*  Get the coordinates of the tile pointed by the mouse */

    in->mouseX /= TILE_SIZE;
    in->mouseY /= TILE_SIZE;

    in->mouseX *= TILE_SIZE;
    in->mouseY *= TILE_SIZE;

	//return 0;
}


/**
 *\fn void keyboardActionGame(Input *in, Map *m, Cursor *cursor)
 *perform action command by keyboard action
 *\param[in,out] in the input structure
 *\param[in,out] m the map to update
 *\param[in,out] cursor the cursor structure
 */
void keyboardActionGame(SDL_Surface *screen, Input *in, Map *m, Cursor *cursor)
{
    /*  Recover the coordinates of the mouse */

    cursor->x = in->mouseX;
    cursor->y = in->mouseY;

    /*  Horizontal scrolling */

    if(in->key[SDLK_RIGHT])
    {
        if(m->xScroll < (m->lvl->width+1)*TILE_SIZE-m->screenWidth)
                m->xScroll+= 5;
        else
        {
            extendMap(m);
        }
    }

    else if(in->key[SDLK_LEFT])
    {
        if(m->xScroll > TILE_SIZE)
                m->xScroll-= 5;
    }

    /*  Back-up of the map */

    if(in->key[SDLK_k])
    {
        saveMap(screen, m);
        in->key[SDLK_k] = 0;
    }

    /*  Reinitialization of the map */

    else if(in->key[SDLK_DELETE])
    {
        reinitMap(m);
        in->key[SDLK_DELETE] = 0;
    }

    /*  Addition of a tile at the position of the cursor */

    if(in->mouse[SDL_BUTTON_LEFT])
    {
        switch(cursor->tileID)
        {
        case ENEMY :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'E';
            break;

        case TREE :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'T';
            break;

        case FLOWER :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'P';
            break;

        case CLOUD :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'N';
            break;

        default :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = cursor->tileID;
            break;
        }
    }



    /*  Deletion of the tile pointed by the cursor*/

    else if(in->mouse[SDL_BUTTON_MIDDLE])
    {
        m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 0;
    }

    /*  Copy of the tile pointed by the cursor */

    else if(in->mouse[SDL_BUTTON_RIGHT])
    {
        switch(m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1])
        {
            case 'E' :
                cursor->tileID = ENEMY;
                break;

            case 'T' :
                cursor->tileID = TREE;
                break;

            case 'P' :
                cursor->tileID = FLOWER;
                break;

            case 'N' :
                cursor->tileID = CLOUD;
                break;

            default :
                cursor->tileID = m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1];
                break;
        }
    }

    /*  Scroll the choice of the current tile */

    if(in->mouse[SDL_BUTTON_WHEELDOWN])
    {
        cursor->tileID--;

        if(cursor->tileID < 0){

            cursor->tileID = TILESET_SIZE;
        }
        else if(cursor->tileID > TILESET_SIZE){

            cursor->tileID = 0;
        }

        in->mouse[SDL_BUTTON_WHEELDOWN] = 0;
    }

    else if(in->mouse[SDL_BUTTON_WHEELUP])
    {
        cursor->tileID++;

        if(cursor->tileID < 0){

            cursor->tileID = TILESET_SIZE;
        }
        else if(cursor->tileID > TILESET_SIZE){

            cursor->tileID = 0;
        }

        in->mouse[SDL_BUTTON_WHEELUP] = 0;
    }

    if(in->key[SDLK_e])
    {
        cursor->tileID = ENEMY;
    }
    else if(in->key[SDLK_t])
    {
        cursor->tileID = TREE;
    }
    else if(in->key[SDLK_g])
    {
        cursor->tileID = GROUND;
    }
    else if(in->key[SDLK_c])
    {
        cursor->tileID = COIN;
    }
    else if(in->key[SDLK_r])
    {
        cursor->tileID = ROCK;
    }
    else if(in->key[SDLK_s])
    {
        cursor->tileID = SPRING;
    }
    else if(in->key[SDLK_f])
    {
        cursor->tileID = FLOWER;
    }
    else if(in->key[SDLK_n])
    {
        cursor->tileID = CLOUD;
    }
    else if(in->key[SDLK_b])
    {
        cursor->tileID = VOID;
    }
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
        case SDL_MOUSEBUTTONDOWN :
            in->mouse[event.button.button] = 1;
            break;
        case SDL_MOUSEBUTTONUP :
            in->mouse[event.button.button] = 0;
            break;
        case SDL_QUIT:
            in->quit = 1;
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
 *\param[out] select boolean about selecting the option or quit to title screen
 *\param[in] nb_options the number of options of the menu

 */
int keyboardActionMenu(Input *in,int *cursorPos,int *select,int nb_options)
{
    if(in->key[SDLK_ESCAPE] || in->quit)
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
    return *cursorPos;
}
