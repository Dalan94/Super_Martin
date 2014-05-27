/*!
 *\file input.c
 *\brief
 *\author Xavier COPONET, Glenn HERROU
 *\date 2014-03-18
 */

#include "input.h"

void updateEvents(Input* in)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
            case SDL_KEYDOWN:
                in->key[event.key.keysym.sym] = 1;
                break;
            case SDL_KEYUP:
                if(((event.key.keysym.sym) != SDLK_y) && ((event.key.keysym.sym) != SDLK_n))
                {
                    in->key[event.key.keysym.sym] = 0;
                }
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
}

void keyboardActionGame(SDL_Surface *screen, Input *in, Map *m, Cursor *cursor, SDLKey *kc)
{
    /*  Recover the coordinates of the mouse */

    cursor->x = in->mouseX;
    cursor->y = in->mouseY;

    /*  Horizontal scrolling */

    if(in->key[kc[1]])
    {
        if(m->xScroll < (m->lvl->width+1)*TILE_SIZE-m->screenWidth)
                m->xScroll+= 5;
        else
        {
            extendMap(m);
        }
    }

    else if(in->key[kc[0]])
    {
        if(m->xScroll > TILE_SIZE)
                m->xScroll-= 5;
    }

    /*  Back-up of the map */

    if(in->key[kc[2]])
    {
        saveMap(screen, m);
        in->key[kc[2]] = 0;
    }

    /*  Reinitialization of the map */

    else if(in->key[kc[3]])
    {
        resetMap(m);
        in->key[kc[3]] = 0;
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

        case PLATFORMV :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'A';
            break;

        case PLATFORMH :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'B';
            break;

        case FLOWER :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'P';
            break;

        case CLOUD :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'N';
            break;
        case HAMMER :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'C';
            break;

        case HEART :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'H';
            break;

        case ADDLIFE :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'L';
            break;

        case CANON_L :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'F';
            break;

        case CANON_R :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'G';
            break;
        case CANON_B :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = 'D';
            break;

        default :
            m->lvl->map[cursor->y / TILE_SIZE][((m->xScroll + cursor->x) / TILE_SIZE)-1] = cursor->tileID;
            break;
        }
    }

    if(in->key[SDLK_SPACE])
    {
        if(in->mouse[SDL_BUTTON_LEFT])
        {
        fillRect(m, cursor->y / TILE_SIZE, ((m->xScroll + cursor->x) / TILE_SIZE)-1, cursor->tileID );
        }
    }
    else if(in->key[SDLK_RCTRL] || in->key[SDLK_LCTRL])
    {
        if(in->mouse[SDL_BUTTON_LEFT])
        {
        fillLine(m, cursor->y / TILE_SIZE, ((m->xScroll + cursor->x) / TILE_SIZE)-1, cursor->tileID );
        }
    }
    else if(in->key[SDLK_RSHIFT] || in->key[SDLK_LSHIFT])
    {
        if(in->mouse[SDL_BUTTON_LEFT])
        {
        fillColumn(m, cursor->y / TILE_SIZE, ((m->xScroll + cursor->x) / TILE_SIZE)-1, cursor->tileID );
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

            case 'A' :
                cursor->tileID = PLATFORMV;
                break;

            case 'B' :
                cursor->tileID = PLATFORMH;
                break;


            case 'P' :
                cursor->tileID = FLOWER;
                break;

            case 'N' :
                cursor->tileID = CLOUD;
                break;
            case 'C' :
                cursor->tileID = HAMMER;
                break;

            case 'H' :
                cursor->tileID = HEART;
                break;

            case 'L' :
                cursor->tileID = ADDLIFE;
                break;
            case 'F' :
                cursor->tileID = CANON_L;
                break;
            case 'G' :
                cursor->tileID = CANON_R;
                break;
            case 'D' :
                cursor->tileID = CANON_B;
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

    if(in->key[kc[4]])
    {
        cursor->tileID = ENEMY;
    }
    else if(in->key[kc[5]])
    {
        cursor->tileID = TREE;
    }
    else if(in->key[kc[8]])
    {
        cursor->tileID = GROUND;
    }
    else if(in->key[kc[9]])
    {
        cursor->tileID = COIN;
    }
    else if(in->key[kc[10]])
    {
        cursor->tileID = ROCK;
    }
    else if(in->key[kc[11]])
    {
        cursor->tileID = SPRING;
    }
    else if(in->key[kc[17]])
    {
        cursor->tileID = HAMMER;
    }
    else if(in->key[kc[15]])
    {
        cursor->tileID = HEART;
    }
    else if(in->key[kc[16]])
    {
        cursor->tileID = ADDLIFE;
    }
    else if(in->key[kc[6]])
    {
        cursor->tileID = FLOWER;
    }
    else if(in->key[kc[7]])
    {
        cursor->tileID = CLOUD;
    }
    else if(in->key[kc[12]])
    {
        cursor->tileID = VOID;
    }
    else if(in->key[kc[13]])
    {
        cursor->tileID = PLATFORMH;
    }
    else if(in->key[kc[14]])
    {
        in->key[kc[14]] = 0;
        displayHelp(screen, kc);
    }
}

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

int keyboardActionMenu(Input *in,int *cursorPos,int *select,int nb_options)
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
    if(nb_options > OPTIONS_PER_COLUMN)
    {
        if(in->key[SDLK_RIGHT] && *cursorPos < OPTIONS_PER_COLUMN)
        {
            (*cursorPos) += OPTIONS_PER_COLUMN;
            if(*cursorPos >= nb_options)
                (*cursorPos) = nb_options-1;
        }
        if(in->key[SDLK_LEFT] && *cursorPos >= OPTIONS_PER_COLUMN)
        {
            (*cursorPos) -= OPTIONS_PER_COLUMN;
            if(*cursorPos < 0)
                (*cursorPos) = 0;
        }
    }
    return *cursorPos;
}
