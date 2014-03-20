/*!
 * \file input.c
 * \brief Management of keyboard and mouse inputs handled by the game
 * \author Glenn HERROU
 * \date 2014-03-18
 */
#include "input.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>



/**
 *\fn void getInput(Input *input)
 *Set/reset the right variable of the input structure depending on the event polled
 *\param[in,out] input The structure where inputs are saved
 */


void getInput(Input *input){

    SDL_Event event;

/*  Keymapping :
*   Manage the keyboard and mouse inputs and stock them
*/

     while(SDL_PollEvent(&event)){

        switch(event.type){

            case SDL_QUIT :

                exit(0);
                break;

            case SDL_KEYDOWN :

                switch(event.key.keysym.sym){

                    case SDLK_ESCAPE :

                        exit(0);
                        break;

                    case SDLK_DELETE :

                        input->reinit = 1;
                        break;


                    case SDLK_q :

                        input->left = 1;
                        break;

                    case SDLK_d :

                        input->right = 1;
                        break;

                    case SDLK_k :

                        input->save = 1;
                        break;

                    default :

                        break;
                }
                break;

            case SDL_KEYUP :

                switch(event.key.keysym.sym){

                    case SDLK_q :

                        input->left = 0;
                        break;

                    case SDLK_d :

                        input->right = 0;
                        break;

                    default :

                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN :

                switch(event.button.button){

                    case SDL_BUTTON_LEFT :

                        input->add = 1;
                        break;

                    case SDL_BUTTON_MIDDLE :

                        input->remove = 1;
                        break;

                    case SDL_BUTTON_RIGHT :

                        input->copy = 1;
                        break;

                    case SDL_BUTTON_WHEELUP :

                        input->next = 1;
                        break;

                    case SDL_BUTTON_WHEELDOWN :

                        input->previous = 1;
                        break;

                    default :

                        break;
                }
                break;

            case SDL_MOUSEBUTTONUP :

                switch(event.button.button){

                    case SDL_BUTTON_LEFT :

                        input->add = 0;
                        break;

                    case SDL_BUTTON_MIDDLE :

                        input->remove = 0;
                        break;

                    default :

                        break;
                }
                break;
        }
    }


    /*  Record the coordinates of the mouse */

    SDL_GetMouseState(&input->mouseX, &input->mouseY);

    /*  Get the coordinates of the tile pointed by the mouse */

    input->mouseX /= TILE_SIZE;
    input->mouseY /= TILE_SIZE;

    input->mouseX *= TILE_SIZE;
    input->mouseY *= TILE_SIZE;
}

/**
 *\fn void update(Map *m, Input *input, Cursor *cursor)
 *Update the map and the screen following variables of the input structure
 *\param[in,out] m Map to update
 *\param[in,out] input The structure where inputs has been saved
 *\param[in,out] cursor The cursor of the mouse
 */

void update(Map *m, Input *input, Cursor *cursor){

    /*  Recover the coordinates of the mouse */

    cursor->x = input->mouseX;
    cursor->y = input->mouseY;

    /*  Manage the horizontal scrolling of the map */

    if(input->left == 1){

        scrolling(m, LEFT);
    }

    else if(input->right == 1){

        scrolling(m, RIGHT);
    }


    /*  Manage the addition of a tile */

    if(input->add == 1){

        m->lvl->map[cursor->y / TILE_SIZE][(m->xScroll + cursor->x) / TILE_SIZE] = cursor->tileID;
    }

    /*  Manage the suppression of a tile */

    else if(input->remove == 1){

        m->lvl->map[cursor->y / TILE_SIZE][(m->xScroll + cursor->x) / TILE_SIZE] = 0;
        cursor->tileID = 0;
    }

    /*  Scroll the choice of the current tile */

    if(input->previous == 1){

        cursor->tileID--;

        if(cursor->tileID < 0){

            cursor->tileID = TILESET_LAST - 1;
        }

        else if(cursor->tileID > TILESET_LAST){

            cursor->tileID = 0;
        }

        input->previous = 0;
    }

    if(input->next == 1){

        cursor->tileID++;

        if(cursor->tileID < 0){

            cursor->tileID = TILESET_LAST - 1;
        }

        else if(cursor->tileID > TILESET_LAST){

            cursor->tileID = 0;
        }

        input->next = 0;
    }

    /*  Manage the copy of a tile */

    if(input->copy == 1){

        cursor->tileID = m->lvl->map[cursor->y / TILE_SIZE][(m->xScroll + cursor->x) / TILE_SIZE];
        input->copy = 0;
    }

    /*  Manage the reinitialization of the ap */

    if(input->reinit == 1){

        reinitMap(m);
        input->reinit = 0;
    }

    /*  Manage the back-up of the map */

    if(input->save == 1){

        saveMap(m);
        input->save = 0;
    }

    /*  Manage the loading of a map on the screen */


    /*  Add a delay to slowdown the scrolling */

    if(input->left == 1 || input->right == 1){

       SDL_Delay(30);
    }
}
