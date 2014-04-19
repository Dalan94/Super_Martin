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
                //return 1;
                break;
            case SDL_KEYUP:
                in->key[event.key.keysym.sym] = 0;
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
 *\param[in,out] in the cursor structure
 */
void keyboardActionGame(Input *in, Map *m, Cursor *cursor)
{
    /*  Recover the coordinates of the mouse */

    cursor->x = in->mouseX;
    cursor->y = in->mouseY;

    /*  Horizontal scrolling */

    if(in->key[SDLK_LEFT])
        scrolling(m, LEFT, TILE_SIZE);

    else if(in->key[SDLK_RIGHT])
        scrolling(m, RIGHT, TILE_SIZE);

    /*  Back-up of the map */

    if(in->key[SDLK_s])
    {
        saveMap(m);
        in->key[SDLK_s] = 0;
    }

    /*  Reinitialization of the map */

    else if(in->key[SDLK_DELETE])
    {
        reinitMap(m);
        in->key[SDLK_DELETE] = 0;
    }

    /*  Addition of a tile at the position of the cursor */

    if(in->mouse[SDL_BUTTON_LEFT])
        m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = cursor->tileID;


    /*  Deletion of the tile pointed by the cursor*/

    else if(in->mouse[SDL_BUTTON_MIDDLE])
    {
        m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 0;
        cursor->tileID = 0;
    }

    /*  Copy of the tile pointed by the cursor */

    else if(in->mouse[SDL_BUTTON_RIGHT])
        cursor->tileID = m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1];

    /*  Scroll the choice of the current tile */

    if(in->mouse[SDL_BUTTON_WHEELDOWN])
    {
        printf("down:%d\n", in->mouse[SDL_BUTTON_WHEELDOWN]);
        cursor->tileID--;

        if(cursor->tileID < 0){

            cursor->tileID = TILESET_LAST;
        }

        else if(cursor->tileID > TILESET_LAST){

            cursor->tileID = 0;
        }

        in->mouse[SDL_BUTTON_WHEELDOWN] = 0;
    }

    else if(in->mouse[SDL_BUTTON_WHEELUP])
    {
        printf("up:%d\n", in->mouse[SDL_BUTTON_WHEELUP]);

        cursor->tileID++;

        if(cursor->tileID < 0){

            cursor->tileID = TILESET_LAST;
        }

        else if(cursor->tileID > TILESET_LAST){

            cursor->tileID = 0;
        }

        in->mouse[SDL_BUTTON_WHEELUP] = 0;
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
void keyboardActionMenu(Input *in,int *cursorPos,int *select,int nb_options)
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
}
