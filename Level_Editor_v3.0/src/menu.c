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
 *\param[in,out] go main loop validation
 *\param[out] s sound system
 *\return 1 si la touche entrée a été activée
 */


int menu(SDL_Surface *screen,int pos_cursor)
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int previous_time=0;
    int current_time=0;
    int select=1;
    int nb_options=2;
    char **options;
    int i;
    int taille_texte;


    Input in;

    SDL_Rect posText={0,0,0,0};

    /*  Waiting screen */

    waiting = imageLoadAlpha("../Super_Martin/sprites/Background/desert_hills_2.png");
    posWait.x = 0;
    posWait.y = 0;

    if ((options=(char **)malloc(nb_options*sizeof(char*))) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    for (i=0 ; i<nb_options ; i++)
    {
        if ((options[i]=(char *)malloc(MAX_LENGTH_FILE_NAME*sizeof(char))) == NULL)
        {
            printf("\nProbleme allocation memoire\n");
            perror("");
            exit(0);
        }
    }

    options[1] = "Nouvelle map";
    options[0] = "Editer une map existante";
    memset(&in,0,sizeof(in));

    while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN])
   {
        updateWaitEvents(&in);
        keyboardActionMenu(&in,&pos_cursor,&select,nb_options);

        waitFPS(&previous_time,&current_time);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        for (i=0 ; i < nb_options ; i++)
        {
            posText.x = 150;
            taille_texte=screen->h / nb_options;
            if (taille_texte > 60)
                taille_texte=60;
            posText.y = screen->h / (1+nb_options) * (i+1) - taille_texte/2;
            printText(screen,&posText,options[i],0,0,0,"../Super_Martin/polices/ubuntu.ttf",taille_texte,1);
            if(i == pos_cursor)
            {
                posText.x = 70;
                printText(screen,&posText,"=>",0,0,0,"../Super_Martin/polices/ubuntu.ttf",taille_texte,1);
            }
        }

        SDL_Flip(screen);

    }

    SDL_FreeSurface(waiting);

    free(options);

    return select;
}

int menuTileSet(SDL_Surface *screen, int pos_cursor)
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int previous_time=0;
    int current_time=0;
    int select=1;
    int nb_tileSet = 5;
    char **tileSet_list;
    int i;
    int text_size;

    Input in;

    SDL_Rect posText={0,0,0,0};

    /*  Waiting screen */

    waiting = imageLoadAlpha("../Super_Martin/sprites/Background/desert_hills_2.png");
    posWait.x = 0;
    posWait.y = 0;

    if ((tileSet_list=(char **)malloc(nb_tileSet*sizeof(char*))) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    for (i=0 ; i<nb_tileSet ; i++)
    {
        if ((tileSet_list[i]=(char *)malloc(MAX_LENGTH_FILE_NAME*sizeof(char))) == NULL)
        {
            printf("\nProbleme allocation memoire\n");
            perror("");
            exit(0);
        }
    }

    tileSet_list[0] = "Grassland";
    tileSet_list[1] = "Snow";
    tileSet_list[2] = "Forest";
    tileSet_list[3] = "Beach";
    tileSet_list[4] = "Desert";

    memset(&in,0,sizeof(in));

    while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN])
   {
        updateWaitEvents(&in);
        keyboardActionMenu(&in,&pos_cursor,&select,nb_tileSet);

        //waitFPS(&previous_time,&current_time);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        for (i=0 ; i < nb_tileSet ; i++)
        {
            posText.x = 150;
            text_size=screen->h / nb_tileSet;
            if (text_size > 60)
                text_size=60;
            posText.y = screen->h / (1+nb_tileSet) * (i+1) - text_size/2;
            printText(screen,&posText,tileSet_list[i],0,0,0,"../Super_Martin/polices/ubuntu.ttf",text_size,1);
            if(i == pos_cursor)
            {
                posText.x = 70;
                printText(screen,&posText,"=>",0,0,0,"../Super_Martin/polices/ubuntu.ttf",text_size,1);
            }
        }

        SDL_Flip(screen);

    }

    SDL_FreeSurface(waiting);


    free(tileSet_list);

    return select;
}


