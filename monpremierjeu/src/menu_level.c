/*!
 * \file    menu_level.c
 * \brief   Menu gerant le choix du niveau
 * \author  Remi BERTHO
 * \date    15/03/14
 * \version 2.0 (implémentation de la gestion des event)
 */

 #include "menu_level.h"

/**
 *\fn int menuLevel(SDL_Surface *screen,char level_name[TAILLE_MAX_NOM_FICHIER],Sound *s)
 *  Menu pour choisr le niveau
 *\param[out] screen l'écran de jeu
 *\param[out] level_name le nom du level que l'on va vouloir lancer
 *\param[in] s la musique de fond
 */
int menuLevel(SDL_Surface *screen,char level_name[TAILLE_MAX_NOM_FICHIER],Sound *s)
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int continuer=1;
    int previous_time=0;
    int current_time=0;
    int play_lvl=1;
    int nb_lvl;
    char **level_names;
    int i;
    int taille_texte;
    int pos_curseur=0;

    Input in;
    SDL_Event event;

    SDL_Rect posText={0,0,0,0};
    SDL_Color black = {0, 0, 0}; /*couleur pour le texte*/

    /*winting screen */
    waiting = imageLoadAlpha("sprites/Background/desert_hills_2.png");
    posWait.x = 0;
    posWait.y = 0;

    level_names=readLevelFile(&nb_lvl);



    memset(&in,0,sizeof(in));

    while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN])
    {
        updateWaitEvents(&in);
        keyboardActionMenu(&in,&pos_curseur,&play_lvl,nb_lvl);

        waitFPS(&previous_time,&current_time);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        for (i=0 ; i < nb_lvl ; i++)
        {
            posText.x = 150;
            taille_texte=screen->h / nb_lvl;
            if (taille_texte > 60)
                taille_texte=60;
            posText.y = screen->h / (1+nb_lvl) * (i+1) - taille_texte/2;
            printText(screen,&posText,level_names[i],0,0,0,"polices/ubuntu.ttf",taille_texte,1);
            if(i == pos_curseur)
            {
                posText.x = 70;
                printText(screen,&posText,"=>",0,0,0,"polices/ubuntu.ttf",taille_texte,1);
            }
        }

        SDL_Flip(screen);

    }

    SDL_FreeSurface(waiting);

    sprintf(level_name,"level/%s.lvl",level_names[pos_curseur]);

    closeLevelList(level_names,nb_lvl);

    FMOD_ChannelGroup_Stop(s->channel);

    return play_lvl;
}
