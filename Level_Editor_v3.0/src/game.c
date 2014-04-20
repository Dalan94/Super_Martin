/*!
 * \file game.c
 * \brief contient les fonction liées au jeu
 * \author Xavier COPONET
 * \date 2014-02-27
 */



#include "game.h"




/**
 *\fn void play(SDL_Surface *screen,char *level_name)
 *contient la boucle principale du jeu qui appelle les fonctions
 *\param[in,out] screen L'écran de jeu
 *\param[in] lvel_name le nom du niveau
 */

void play(SDL_Surface *screen, char *level_name){

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
    SDL_Surface *watch;
    SDL_Rect posWatch = {10,10,0,0};

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


    while(!in.key[SDLK_ESCAPE] && go){

        /*  Recovery and management of inputs */

        updateEvents(&in);


        if(in.quit)
            go = 0;

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(background,NULL,screen,&posBack);
        keyboardActionGame(&in,m,cursor);
        updateScreenMap(screen,m, m->lvl->tileSet, cursor);

        SDL_Flip(screen);
    }

    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));
    SDL_Flip(screen);

    /*  Freeing of allocated memory */

    SDL_FreeSurface(background);
    freeMap(m);
}


/**
 *\fn void printGameOver(SDL_Surface *screen,int *continuer,Input *in)
 *affiche le message de game overflow_error
 *\param[out] screen l'écran de jeu
 */
void printGameOver(SDL_Surface *screen,int *continuer,Input *in){
    SDL_Surface *gameOver = NULL;
    SDL_Rect posGame;


    Sound *s;
    s = createSound();
    playMusic(s,"../Super_Martin/sound/chopin1.mp3");

    gameOver = IMG_Load("../Super_Martin/sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(gameOver, SDL_SRCALPHA, 200);
    SDL_BlitSurface(gameOver,NULL,screen,&posGame);

    printText(screen,NULL,"GAME OVER",186,38,18,"polices/manga.ttf",65,1);
    SDL_Flip(screen);

    SDL_Delay(1500); //pause pour éviter de quitter l'écran instantanément si joueur appuit sur une touche lors de sa mort

//    while(!updateEvents(in));
    *continuer = 0;
    SDL_FreeSurface(gameOver);
    freeSound(s);

}

/**
 *\fn void printPause(SDL_Surface *screen, Input *in, int *time,int *continuer)
 * Met en pause le jeu
 *\param[out] screen l'écran de jeu
 *\param[out] time le temps restant
 *\param[in] in la structure input
 *\param[out] le booléen de main loop de la fonction jouer
 */
void printPause(SDL_Surface *screen, Input *in, int *time, int *continuer)
{
    SDL_Surface *gameOver = NULL;
    SDL_Rect posGame;

    int time_pause=*time;

    gameOver = IMG_Load("../Super_Martin/sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(gameOver, SDL_SRCALPHA, 200);
    SDL_BlitSurface(gameOver,NULL,screen,&posGame);


    printText(screen,NULL,"PAUSE",186,38,18,"../Super_Martin/polices/manga.ttf",65,1);
    SDL_Flip(screen);
    in->key[SDLK_p] = 0;

    while(!in->key[SDLK_p] && *continuer){

        updateEvents(in);
        if(in->quit)
            *continuer = 0;

    }
    SDL_FreeSurface(gameOver);

    *time=time_pause;
    in->key[SDLK_p] = 0;
}

Uint32 decomptage(Uint32 intervalle,void* parametre){
    int *time = parametre;
    (*time)--;
    return intervalle;
}
