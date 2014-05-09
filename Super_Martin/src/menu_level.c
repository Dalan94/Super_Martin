/*!
 * \file    menu_level.c
 * \brief   Menu gerant le choix du niveau
 * \author  Remi BERTHO
 * \date    15/03/14
 * \version 2.0 (implémentation de la gestion des event)
 */

 #include "menu_level.h"

/**
 *\fn int menuLevel(SDL_Surface *screen,char level_name[MAX_SIZE_FILE_NAME],Sound *sound_sys)
 *  Menu to choose the lvl
 *\param[out] screen game screen
 *\param[out] level_name the name of the level we will want to launch
 *\param[in,out] sound_sys the sound system
 *\return 1 if a level has been choosen, 0 if not
 */

int menuLevel(SDL_Surface *screen,char level_name[MAX_SIZE_FILE_NAME],Sound *sound_sys, char player_name[MAX_SIZE_FILE_NAME], Player *player, int *go, int *nb_lvl)
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int previous_time=0;
    int current_time=0;
    int play_lvl=1;

    char **level_names;
    int i;
    int taille_texte;
    int pos_curseur=0;

    Input in;

    SDL_Rect posText={0,0,0,0};

    /*winting screen */
    waiting = imageLoadAlpha("sprites/Background/menu_background.png");
    posWait.x = 0;
    posWait.y = 0;

    //loadPlayer("save/.save", player_name, player);
    level_names=readLevelFile("level/level", nb_lvl);

    memset(&in,0,sizeof(in));

    while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN])
    {
        updateWaitEvents(&in,go);
        if(pos_curseur>=0)
            keyboardActionMenu(&in,&pos_curseur,&play_lvl,min(player->levelMax, *nb_lvl));
        if(in.key[SDLK_ESCAPE])
            pos_curseur = -1;
        waitFPS(&previous_time,&current_time);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        if(pos_curseur>=0)
        {
            for (i=0 ; i < min(player->levelMax, *nb_lvl) ; i++)
            {

                posText.x = -1;
                taille_texte=screen->h / *nb_lvl;
                if (taille_texte > 60)
                    taille_texte=60;
                posText.y = screen->h / (1+*nb_lvl) * (i+1) - taille_texte/2;
                printText(screen,&posText,level_names[i],0,0,0,"polices/ubuntu.ttf",taille_texte,1);
                if(i != pos_curseur)
                    printText(screen,&posText,level_names[i],0,0,0,"polices/ubuntu.ttf",taille_texte,1);
                else
                    printText(screen,&posText,level_names[i],255,60,30,"polices/ubuntu.ttf",taille_texte,1);

            }
        }

        SDL_Flip(screen);

    }

    SDL_FreeSurface(waiting);

    if(pos_curseur>=0)
        sprintf(level_name,"level/%s.lvl",level_names[pos_curseur]);

    closeLevelList(level_names,*nb_lvl);

    stopSound(sound_sys,1);

    return pos_curseur;
}
