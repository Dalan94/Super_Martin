/*!
 * \file menu.c
 * \brief contient les fonction liées au menu
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#include "menu.h"

/**
 *\fn int menu(SDL_Surface *screen)
 *affiche le menu à l'écran
 *\param[out] screen l'écran
 *\return 1 si la touche entrée a été activée
 */
int menu(SDL_Surface *screen,int *continuer){
    SDL_Surface *waiting;
    SDL_Rect posWait,posText;
    int printingText = 1;
    int ret = 0;

    SDL_Event event;

    SDL_TimerID timer; /* Variable pour stocker le numéro du timer */

    SDL_Color black = {0, 0, 0}; /*couleur pour le texte*/


    /*initialisation du systeme audio*/

    Sound *s = createSound();
    playMusic(s,"sound/Lorena.mp3");

    /* *********************** */

    /*winting screen */
    waiting = IMG_Load("sprites/title.jpg");
    posWait.x = 0;
    posWait.y = 0;

        /*position texte*/
    /*posText.x = screen->w/2-150;
    posText.y = screen->h/2-65;*/
    /* ************************ */

    /*appel du timer*/
    timer = SDL_AddTimer(1000,blinkText,&printingText); /* Démarrage du timer */



    while(*continuer && !ret){
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                *continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        *continuer = 0;
                        break;
                    case SDLK_RETURN:

                        ret = 1;

                        break;
                    default : ;
                }
                break;
        }

        SDL_BlitSurface(waiting, NULL, screen, &posWait);
        if(printingText)
            printText(screen,NULL,"Press Enter",black,"polices/sherwood.ttf",65,1); //argument 2 NULL pour centrer le texte
        SDL_Flip(screen);
    }



    freeSound(s);

    SDL_FreeSurface(waiting);

    SDL_RemoveTimer(timer); /* Arrêt du timer */

    return ret;
}

Uint32 blinkText(Uint32 intervalle, void *parametre){
    int *printingText = parametre;

    *printingText ^= 1;

    if(*printingText){
        return 1000;
    }

    return 600;
}




