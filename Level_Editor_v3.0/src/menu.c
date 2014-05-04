/*!
 * \file menu.c
 * \brief contient les fonction liées au menu
 * \author Glenn HERROU
 * \date 2014-04-20
 */

#include "menu.h"

/**
 *\fn int menu(SDL_Surface *screen, int *choice, int *go)
 *Display the menu on the screen
 *\param[out] screen l'écran
 *\param[out] choice the option selected
 *\param[out] go the main loop validation
 *\return 1 if an option has been selected
 */


int menu(SDL_Surface *screen,int *choice, int *go)
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int previous_time=0;
    int current_time=0;
    int select=1;
    int nb_options=4;
    char **options;
    int i;
    int text_size;
    int pos_cursor = 0;


    Input in;

    SDL_Rect posText={0,0,0,0};

    /*  Waiting screen */

    waiting = imageLoadAlpha("../Super_Martin/sprites/Background/menu_background.png");
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

    strcpy(options[3],  "Controls");
    strcpy(options[2],  "Delete a map");
    strcpy(options[1], "Edit a map");
    strcpy(options[0],  "New map");

    memset(&in,0,sizeof(in));

    while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN])
   {
        updateWaitEvents(&in);
        if(in.key[SDLK_ESCAPE])
                *go = 0;
        keyboardActionMenu(&in,&pos_cursor,&select,nb_options);

        waitFPS(&previous_time,&current_time);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        for (i=0 ; i < nb_options ; i++)
        {
            posText.x = -1;
            text_size=screen->h / nb_options;
            if (text_size > 60)
                text_size=60;
            posText.y = screen->h / (1+nb_options) * (i+1) - text_size/2;

            if(i != pos_cursor)
                printText(screen,&posText,options[i],0,0,0,"polices/ubuntu.ttf",text_size,1);
            else
                printText(screen,&posText,options[i],255,60,30,"polices/ubuntu.ttf",text_size,1);
        }

        SDL_Flip(screen);

    }
    *choice=pos_cursor;
    SDL_FreeSurface(waiting);
    for (i=0 ; i<nb_options ; i++)
        free(options[i]);
    free(options);

    return select;
}

int menuTileSet(SDL_Surface *screen, char tileSet_name[MAX_LENGTH_FILE_NAME])
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int previous_time=0;
    int current_time=0;
    int select=1;
    int nb_tileSet = 6;
    char **tileSet_list;
    int i;
    int text_size;
    int pos_cursor=0;
    Input in;

    SDL_Rect posText={0,0,0,0};

    /*  Waiting screen */

    waiting = imageLoadAlpha("../Super_Martin/sprites/Background/menu_background.png");
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

    strcpy(tileSet_list[0], "Grassland");
    strcpy(tileSet_list[1], "Snow");
    strcpy(tileSet_list[2], "Forest");
    strcpy(tileSet_list[3], "Beach");
    strcpy(tileSet_list[4], "Desert");
    strcpy(tileSet_list[5], "Mountains");

    memset(&in,0,sizeof(in));

    while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN])
   {
        updateWaitEvents(&in);
        keyboardActionMenu(&in,&pos_cursor,&select,nb_tileSet);

        waitFPS(&previous_time,&current_time);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        for (i=0 ; i < nb_tileSet ; i++)
        {
            posText.x = -1;
            text_size=screen->h / (nb_tileSet*2);
            if (text_size > 60)
                text_size=60;
            posText.y = screen->h / (1+nb_tileSet) * (i+1) - text_size/2;
            if(i != pos_cursor)
                printText(screen,&posText,tileSet_list[i],0,0,0,"polices/ubuntu.ttf",text_size,1);
            else
                printText(screen,&posText,tileSet_list[i],255,60,30,"polices/ubuntu.ttf",text_size,1);
        }

        SDL_Flip(screen);

    }

    SDL_FreeSurface(waiting);
    sprintf(tileSet_name,"../Super_Martin/level/Empty_levels/%s.lvl",tileSet_list[pos_cursor]);
    for (i=0 ; i<nb_tileSet ; i++)
        free(tileSet_list[i]);
    free(tileSet_list);

    return select;
}


