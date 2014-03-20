/*!
 * \file game.c
 * \brief Contains the principal function of the game
 * \author Xavier COPONET, Glenn HERROU
 * \date 2014-03-18
 */


#include "game.h"



/**
 *\fn void play(SDL_Surface *screen,char *level_name)
 *Contains the infinite loop of the game, call the main functions
 *\param[in,out] screen Game screen
 *\param[in] level_name Level name
 */

void play(SDL_Surface *screen, char *level_name){

    int go = 1;

    /*  Declaration of the structures */

    Map *m;
    Level *lvl;
    Input *_input;
    Cursor *mouse;

    /*  Declaration of the surfaces */

    SDL_Surface *background = NULL;
    SDL_Surface *background2 = NULL;
    SDL_Rect posBack;
    SDL_Event event;

    _input = (Input *)malloc(sizeof(Input));
    if(_input == NULL){
        perror("Error allocating memory");
        exit(errno);
    }

    mouse = (Cursor *)malloc(sizeof(Cursor));
    if (mouse == NULL){
        perror("Error allocating memory");
        exit(errno);
    }
    /*  Fill the screen with blank tiles */

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, TRANS_R, TRANS_G, TRANS_B));

    posBack.x = 0;
    posBack.y = 0;

    /*  Initialization of the map and the level */

    lvl = openLevel(level_name);
    m = initMap(lvl,screen);

    /*  Loading of the differents background */

    background = IMG_Load(m->lvl->background);

    if(background == NULL){

        perror("Error : couldn't load background sprite");
        exit(errno);
    }

    background2 = SDL_DisplayFormatAlpha(background);

    if(background2 == NULL){

        perror("Error couldn't load background sprite");
        exit(errno);
    }

    SDL_FreeSurface(background);

    /*  Enable the key repetition */

    SDL_EnableKeyRepeat(100,100);

    /* Main loop of the function */

    while(go){

        /*  Get a keyboard or a mouse input and change the variable of _input corresponding to this input */

        getInput(_input);

        /*  Fill the screen with blank tiles */

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,TRANS_R,TRANS_G,TRANS_B));

        /*  Blit the background */

        SDL_BlitSurface(background2,NULL,screen,&posBack);

        /*  Consider the result of the input and update */

        update(m, _input, mouse);

        /*  Update the screen */

        updateScreenMap(screen,m,"sprites/tilesetok.png", mouse);


        /*  Display the screen */

        SDL_Flip(screen);

    } //while

    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,TRANS_R,TRANS_G,TRANS_B));
    SDL_Flip(screen);

    /*Free*/
    SDL_FreeSurface(background2);
    free(mouse);
    free(_input);
    freeMap(m);
}
