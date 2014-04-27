/*!
 * \file menu.c
 * \brief containes some functions tied to the title and main menu
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#include "menu.h"

/**
 *\fn int titleMenu(SDL_Surface *screen,FMOD_SYSTEM *sys)
 *print the title menu on the screen
 *\param[out] screen the game screen
 *\param[in,out] go main loop validation
 *\param[out] sys sound system
 *\return 1 if the enter key has been pushed
 */

int titleMenu(SDL_Surface *screen,int *go,Sound *sound_sys)

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
    playMusic("sound/Lorena.mp3",sound_sys);

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

/**
 *\fn int mainMenu(SDL_Surface *screen,int *go,Sound *sound_sys)
 *print the main menu on the screen
 *\param[out] screen the game screen
 *\param[in,out] go main loop validation
 *\param[out] sys sound system
 *\return the number of the menu which is choosen, -1 if esc
 */
int mainMenu(SDL_Surface *screen,int *go,Sound *sound_sys)
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int nb_menu = 2;
    char menu_names[2][MAX_SIZE_FILE_NAME]={"Choose level","Options"};
    int ret = 1;
    int i;
    int text_size;
    int pos_curseur=0;

    Input in;

    SDL_Rect posText={0,0,0,0};

    /*winting screen */
    waiting = imageLoadAlpha("sprites/Background/desert_hills_2.png");
    posWait.x = 0;
    posWait.y = 0;

    memset(&in,0,sizeof(in));

    while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN])
    {
        updateWaitEvents(&in,go);
        keyboardActionMenu(&in,&pos_curseur,&ret,nb_menu);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        for (i=0 ; i < nb_menu ; i++)
        {
            posText.x = 150;
            text_size=screen->h / nb_menu;
            if (text_size > 60)
                text_size=60;
            posText.y = screen->h / (1+nb_menu) * (i+1) - text_size/2;
            if(i != pos_curseur)
                printText(screen,&posText,menu_names[i],0,0,0,"polices/ubuntu.ttf",text_size,1);
            else
            {
                printText(screen,&posText,menu_names[i],255,60,30,"polices/ubuntu.ttf",text_size,1);
            }
        }

        SDL_Flip(screen);

    }

    SDL_FreeSurface(waiting);
    if(!ret)
        return -1;

    return pos_curseur;
}
