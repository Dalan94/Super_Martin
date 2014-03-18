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
 *\param[in,out] continuer main loop validation
 *\param[out] s sound system
 *\return 1 si la touche entrée a été activée
 */
int menu(SDL_Surface *screen,int *continuer,Sound *s){
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int printingText = 1;
    int previous_printing_text=0;
    int ret = 0;
    int previous_time=0;
    int current_time=0;
    int event_appear=1;


    SDL_Event event;

    SDL_TimerID timer; /* Variable pour stocker le numéro du timer */

    SDL_Color black = {0, 0, 0}; /*couleur pour le texte*/


    /*initialisation du systeme audio*/

   // s = createSound();
    playMusic(s,"sound/Lorena.mp3");

    /* *********************** */

    /*winting screen */
    waiting = imageLoadAlpha("sprites/Background/desert_hills_2.png");
    posWait.x = 0;
    posWait.y = 0;


    /* ************************ */

    /*appel du timer*/
    timer = SDL_AddTimer(1000,blinkText,&printingText); /* Démarrage du timer */



    while(*continuer && !ret){
        SDL_PollEvent(&event);
        event_appear = 1;
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
            default : event_appear = 0;
        }

        if(printingText != previous_printing_text)
        {
            event_appear = 1;
            previous_printing_text = printingText;
        }


        waitFPS(&previous_time,&current_time);

        if(event_appear)
        {
            SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

            SDL_BlitSurface(waiting, NULL, screen, &posWait);

            if (printingText)
                printText(screen,NULL,"Press Enter",black,"polices/sherwood.ttf",65,1); //argument 2 NULL pour centrer le texte

            SDL_Flip(screen);
        }
    }




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




