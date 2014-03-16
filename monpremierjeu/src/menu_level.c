/*!
 * \file    menu_level.c
 * \brief   Menu gerant le choix du niveau
 * \author  Remi BERTHO
 * \date    15/03/14
 * \version 1.0
 */

 #include "menu_level.h"


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

    SDL_Event event;
    SDL_Rect posText={0,0,0,0};
    SDL_Color black = {0, 0, 0}; /*couleur pour le texte*/

    /*winting screen */
    waiting = IMG_Load("sprites/Background/desert_hills_2.png");
    posWait.x = 0;
    posWait.y = 0;

    level_names=readLevelFile(&nb_lvl);

    SDL_EnableKeyRepeat(0,100);

    while(continuer){
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                play_lvl = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        continuer = 0;
                        play_lvl = 0;
                        break;
                    case SDLK_RETURN:
                        continuer=0;
                        break;
                    case SDLK_UP:
                        pos_curseur--;
                        if (pos_curseur < 0)
                            pos_curseur=nb_lvl-1;
                        break;
                    case SDLK_DOWN:
                        pos_curseur++;
                        if (pos_curseur >= nb_lvl)
                            pos_curseur=0;
                        break;
                    default : ;
                }
                break;
            default :;
        }

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
            printText(screen,&posText,level_names[i],black,"polices/ubuntu.ttf",taille_texte,1);
            if(i == pos_curseur)
            {
                posText.x = 70;
                printText(screen,&posText,"=>",black,"polices/ubuntu.ttf",taille_texte,1);
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
