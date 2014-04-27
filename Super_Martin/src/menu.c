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
int menu(SDL_Surface *screen,int *go,Sound *s)
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int printingText = 1;
    int previous_printing_text=0;
    int ret = 0;
    int previous_time=0;
    int current_time=0;
    int event_appear=1;


    Input in;
    memset(&in,0,sizeof(in));

    SDL_TimerID timer; /* Variable pour stocker le numéro du timer */


    /*initialisation du systeme audio*/
    playMusic(s,"sound/Lorena.mp3");
    soundVolume(s,0);

    /* *********************** */

    /*winting screen */
    waiting = imageLoadAlpha("sprites/Background/desert_hills_2.png");
    posWait.x = 0;
    posWait.y = 0;


    /* ************************ */

    /*appel du timer*/
    timer = SDL_AddTimer(1000,blinkText,&printingText); /* Démarrage du timer */



    while(*go && !ret){
            if(updateEvents(&in,go))
                event_appear = 1;

            if(in.key[SDLK_ESCAPE] || in.quit)
                *go = 0;
            if(in.key[SDLK_RETURN])
                ret = 1;



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
                printText(screen,NULL,"Press Enter",0,0,0,"polices/sherwood.ttf",65,1); //argument 2 NULL pour centrer le texte

            SDL_Flip(screen);
        }
    }

    SDL_FreeSurface(waiting);

    SDL_RemoveTimer(timer); /* Arrêt du timer */

    return ret;
}

/**
 *\fn Uint32 blinkText(Uint32 interval, void *param)
 *toggle the printing text boolean
 *\param[in] interval the interval between two callback of the function
 *\return 1000 if the boolean is right, 600 if not
 */
Uint32 blinkText(Uint32 interval, void *param)
{
    int *printingText = param;

    *printingText ^= 1;

    if(*printingText){
        return 1000;
    }

    return 600;
}




