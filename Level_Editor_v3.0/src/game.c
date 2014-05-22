
/*!
 * \file game.c
 * \brief Contain the main functions of the game
 * \author Xavier COPONET, Glenn HERROU
 * \date 2014-05-15
 */

#include "game.h"

void play(SDL_Surface *screen, char *level_name, SDLKey *kc){

    int go = 1;

    /*  Declaration of the map, the cursor and the input structures*/

    Map *m;
    Input in;
    memset(&in,0,sizeof(in));
    Cursor *cursor;

    cursor = (Cursor *)malloc(sizeof(Cursor));
    if (cursor == NULL){
        perror("Error allocating memory");
        exit(errno);
    }

    /*  Declaration of the surfaces */

    SDL_Surface *background = NULL;
    SDL_Rect posBack;

    /*  Cleaning of the screen */

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    posBack.x = 0;
    posBack.y = 0;

    /*  Initialization of the map and its level */

    m = initMap(screen,level_name);

    /*  Loading of the background */

    background = imageLoadAlpha(m->lvl->background);

    /*  Activation of key repetitions */

    SDL_EnableKeyRepeat(100,100);


    while(go){

        /*  Recovery and management of inputs */

        updateEvents(&in);


        if(in.key[SDLK_ESCAPE] || in.quit)
            printConfirmation(screen, &in, &go);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(background,NULL,screen,&posBack);
        keyboardActionGame(screen, &in,m,cursor, kc);
        updateScreenMap(screen,m, m->lvl->tileSet, cursor);

        SDL_Flip(screen);
    }

    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));
    SDL_Flip(screen);

    /*  Freeing of allocated memory */

    SDL_FreeSurface(background);
    freeMap(m);
}

void printConfirmation(SDL_Surface *screen, Input *in, int *go)
{
    SDL_Surface *Continue = NULL;
    SDL_Rect posContinue, posText;

    Continue = IMG_Load("../Super_Martin/sprites/game-over.jpg");
    posContinue.x = posContinue.y = 0;
    SDL_SetAlpha(Continue, SDL_SRCALPHA, 200);
    SDL_BlitSurface(Continue,NULL,screen,&posContinue);
    char choice[1];
    int text_size;
    *go = 2;

    posText.x = -1;
    posText.y = 300;
    text_size = 30;
    printText(screen, &posText, "Do you really want to quit ? (y/n)", 186, 38, 18, "../Super_Martin/polices/PressStart2P.ttf", text_size, 1);
    SDL_Flip(screen);

    while(*go > 1)
    {
        updateWaitEvents(in);

        posText.x = -1;
        posText.y = 370;

        captureText(screen, posText, choice, 1, 186, 38, 18, "../Super_Martin/polices/PressStart2P.ttf", text_size, go);

        if(choice[0] == 'n')
        {
            *go = 1;
        }
        else if(choice[0] == 'y')
        {
            *go = 0;
        }
        SDL_Flip(screen);
    }

    SDL_FreeSurface(Continue);
}
