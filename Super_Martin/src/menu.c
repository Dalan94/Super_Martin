/*!
 * \file menu.c
 * \brief contains some functions tied to the title and main menu
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#include "menu.h"



int titleMenu(SDL_Surface *screen,int *go,Sound *sound_sys,Input *in)

{
    SDL_Surface *waiting=NULL;
    SDL_Rect posWait;
    int printingText = 1;
    int previous_printing_text=0;
    int ret = 0;
    int previous_time=0;
    int current_time=0;
    int event_appear=1;


    //Input in;
    //memset(&in,0,sizeof(in));

    SDL_TimerID timer; /* Variable pour stocker le numéro du timer */

    playMusic("sound/Lorena.mp3",sound_sys);

    /* *********************** */

    /*winting screen */
    waiting = imageLoadAlpha("sprites/Background/menu_background.png");
    posWait.x = 0;
    posWait.y = 0;


    /* ************************ */

    /*appel du timer*/
    timer = SDL_AddTimer(1000,blinkText,&printingText); /* Démarrage du timer */

    initInput(in); //initilisation des inputs

    while(*go && !ret)
    {

            if(updateEvents(in,go))
                event_appear = 1;

            if(in->key[SDLK_ESCAPE] || in->quit || (in->isJoystick&&in->button[BACK]))
                *go = 0;
            if(in->key[SDLK_RETURN] || (in->isJoystick&&(in->button[A] || in->button[START])))
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
                printText(screen,NULL,"Press Enter",0,0,0,"polices/sherwood.ttf",80,1); //argument 2 NULL pour centrer le texte

            SDL_Flip(screen);
        }
    }

    SDL_FreeSurface(waiting);

    SDL_RemoveTimer(timer); /* Arrêt du timer */

    return ret;
}


Uint32 blinkText(Uint32 interval, void *param)
{
    int *printingText = param;

    *printingText ^= 1;

    if(*printingText)
    {
        return 1000;
    }

    return 600;
}



int mainMenu(SDL_Surface *screen,int *go,Sound *sound_sys,char *player_name, Input *in)
{
    SDL_Surface *waiting=NULL;
    SDL_Rect posWait;
    int nb_menu = 4;
    char menu_names[4][MAX_SIZE_FILE_NAME]={"Start", "Save", "Options", "Delete player"};
    int ret = 1;
    int i;
    int text_size;
    int pos_curseur=0;



    SDL_Rect posText={0,0,0,0};


    playMusic("sound/Lorena.mp3",sound_sys);

    /*waiting screen */
    waiting = imageLoadAlpha("sprites/Background/menu_background.png");
    posWait.x = 0;
    posWait.y = 0;

    memset(&in->key,0,SDLK_LAST*sizeof(char));
    if(in->isJoystick)
        initInput(in);

    while(!in->key[SDLK_ESCAPE] && !in->quit && !in->key[SDLK_RETURN] && (!in->isJoystick||!(in->button[A] || in->button[BACK])))
    {
        updateWaitEvents(in,go);
        if(in->key[SDLK_ESCAPE] || (in->isJoystick&&(in->button[BACK] )))
        {
            SDL_FreeSurface(waiting);
            return -1;
        }
        inputActionMenu(in,&pos_curseur,&ret,nb_menu);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        for (i=0 ; i < nb_menu ; i++)
        {
            posText.x = -1;
            text_size=screen->h / nb_menu;
            if (text_size > 30)
                text_size = 30;
            posText.y = 150 + (screen->h - 350) / (1+nb_menu) * (i+1) - text_size/2;
            posText.x = -1;
            if(i != pos_curseur)
                printText(screen,&posText,menu_names[i],0,0,0,"polices/PressStart2P.ttf",text_size,1);
            else
            {
                printText(screen,&posText,menu_names[i],255,60,30,"polices/PressStart2P.ttf",text_size,1);
            }
        }
        posText.x = -1;
        posText.y = 680;
        printText(screen, &posText, player_name, 0, 0, 0, "polices/PressStart2P.ttf", 30, 1);
        SDL_Flip(screen);

    }

    SDL_FreeSurface(waiting);
    if(!ret)
        return -1;

    return pos_curseur;
}


int menuPlayers(SDL_Surface *screen, char player_name[MAX_SIZE_FILE_NAME], int *go, Sound *sound_sys, Input *in)
{

    SDL_Surface *waiting=NULL;
    SDL_Rect posWait;
    int previous_time=0;
    int current_time=0;
    int choose_player=1;
    int nb_players;
    char **player_names;
    int i;
    int text_size;
    int pos_cursor=0;
    SDL_Rect posText={0,0,0,0};

    /*waiting screen */
    waiting = imageLoadAlpha("sprites/Background/menu_background.png");
    posWait.x = 0;
    posWait.y = 0;

    player_names=readLevelFile( "save/players", &nb_players);

    sprintf(player_names[nb_players-1], "New player");

    memset(&in->key,0,SDLK_LAST*sizeof(char));
    if(in->isJoystick)
        initInput(in);

    while(!in->key[SDLK_ESCAPE] && !in->quit && !in->key[SDLK_RETURN] && (!in->isJoystick||!(in->button[A] || in->button[BACK])))
    {
        updateWaitEvents(in,go);
        if(in->key[SDLK_ESCAPE] || (in->isJoystick&&(in->button[BACK] )))
        {
            choose_player = -1;
        }
        else
        {
            inputActionMenu(in,&pos_cursor,&choose_player, nb_players);

            waitFPS(&previous_time,&current_time);

            SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

            SDL_BlitSurface(waiting, NULL, screen, &posWait);

            for (i=0 ; i < nb_players ; i++)
            {
                posText.x = -1;
                text_size=screen->h / (nb_players+1);
                if (text_size > 30)
                    text_size = 30;
                posText.y = 150 + (screen->h - 350) / (1+nb_players) * (i+1) - text_size/2;
                printText(screen,&posText,player_names[i],0,0,0,"polices/PressStart2P.ttf",text_size,1);
                if(i != pos_cursor)
                    printText(screen,&posText,player_names[i],0,0,0,"polices/PressStart2P.ttf",text_size,1);
                else
                    printText(screen,&posText,player_names[i],255,60,30,"polices/PressStart2P.ttf",text_size,1);

            }

            SDL_Flip(screen);
        }
    }

    SDL_FreeSurface(waiting);

    if(!(strcmp("New player", player_names[pos_cursor])))
    {
        choose_player = 2;
    }
    else
    {
        sprintf(player_name, "%s", player_names[pos_cursor]);
    }
    if(!choose_player)
        return -1;

    closeLevelList(player_names,nb_players);

    return choose_player;
}
