/*!
 * \file    player.c
 * \brief   Management of the player system
 * \author  Glenn HERROU
 * \date    06/05/14
 * \version 1.0
 */

#include "player.h"

int newPlayer(SDL_Surface *screen,char player_name[MAX_SIZE_FILE_NAME],Sound *s,int *go)
{
    SDL_Surface *waiting;
    SDL_Rect posText, posWait;
    int text_size = 25;
    int i, incr, ret = 0;
    int wrong_player = 1;
    int nb_players;
    char **player_list;
    char tmp[MAX_SIZE_FILE_NAME];
    FILE *ptr_file_player;
    char choice[1];
    int res;
    char path[MAX_SIZE_FILE_NAME];

    ptr_file_player = fopen("save/players", "r+");

    if(ptr_file_player == NULL){

        printf("Failed to open file save/players\n");
        exit(1);
    }

    player_list = readLevelFile("save/players", &nb_players);
    sprintf(tmp, "Your player name :");

    Input in;
    memset(&in, 0, sizeof(in));

    choice[0]= 32;

    waiting = imageLoadAlpha("sprites/Background/menu_background.png");
    posWait.x = 0;
    posWait.y = 0;
    SDL_BlitSurface(waiting, NULL, screen, &posWait);

    posText.x = -1;
    posText.y = 200;
    printText(screen, &posText, tmp, 0, 0, 0, "polices/PressStart2P.ttf", text_size, 1);
    SDL_Flip(screen);

    while(wrong_player)
    {
        memset(tmp, 0, sizeof(tmp));
        memset(player_name, 0, sizeof(Player));
        incr = 1;
        wrong_player = 0;
        while(*go && !ret)
        {
            updateWaitEvents(&in, NULL);
            if(in.key[SDLK_ESCAPE])
                *go = 0;
            else if(in.key[SDLK_RETURN])
                ret = 1;
            else
            {
                posText.x = -1;
                posText.y = 250;
                captureText(screen, posText, player_name, MAX_SIZE_FILE_NAME, 0, 0, 0, "polices/PressStart2P.ttf", text_size, go, &ret);
            }
        }
        text_size = 23;
        ret = 0;
        for(i = 0; !ret && *go && i < nb_players-1; i++)
        {
            if(!(strcmp(player_name, player_list[i])))
            {
                posText.x = -1;
                posText.y = 300;

                sprintf(tmp, "%s already exists. Do you want to continue (y/n) ?", player_name);
                printText(screen, &posText, tmp, 0, 0, 0, "polices/PressStart2P.ttf", text_size, 1);
                posText.x = -1;
                posText.y = 350;
                sprintf(tmp, "The progression of %s will be erased ", player_name);
                printText(screen, &posText, tmp, 0, 0, 0, "polices/PressStart2P.ttf", text_size, 1);

                SDL_Flip(screen);
                posText.x = -1;
                posText.y = 400;
                captureText(screen, posText, choice, 1, 0, 0, 0, "polices/PressStart2P.ttf", text_size, go, &ret);

                if(choice[0] == 'n')
                {
                    sprintf(tmp, "Creation aborted  -  Press Enter to continue");
                    ret = 0;
                }
                else if(choice[0] == 'y')
                {
                    sprintf(tmp, "Player %s created  -  Press Enter to continue", player_name);
                    incr = 0;
                    ret = 1;
                }
            }
        }
        if(choice[0] == ' ' && *go)
        {
            sprintf(tmp, "Player %s created  -  Press Enter to continue", player_name);
            ret = 1;
        }
    }


    if(go && ret)
    {
        fseek(ptr_file_player, 0, SEEK_SET);
        fscanf(ptr_file_player, "%d", &nb_players);
        fseek(ptr_file_player, 0, SEEK_SET);
        fprintf(ptr_file_player, "%d", (nb_players+incr));
        fseek(ptr_file_player, 0, SEEK_END);
        if(incr !=0){

            fprintf(ptr_file_player, "%s\n", player_name);
        }

        closeFile(ptr_file_player);
    }
    res = (ret&&*go);
    ret = 0;
    in.key[SDLK_RETURN] = 0;
    while(!ret && *go)
    {
        posText.x = -1;
        posText.y = 450;
        printText(screen, &posText, tmp, 0, 0, 0, "../Super_Martin/polices/PressStart2P.ttf", text_size, 1);
        SDL_Flip(screen);
        updateWaitEvents(&in, NULL);
        if(in.key[SDLK_RETURN])
        {
            ret = 1;
            in.key[SDLK_RETURN] = 0;
        }
    }
    sprintf(path,"configuration/%s.conf",player_name);
    closeFile(openFile(path,"w"));
    SDL_FreeSurface(waiting);
    return res;
}


void loadPlayer(char fileSave[MAX_SIZE_FILE_NAME], char player_name[MAX_SIZE_FILE_NAME], Player *player)
{
    FILE *ptr_file_save;
    int nameFound = 0, i, go = 1;
    char tmp[MAX_SIZE_FILE_NAME];
    char tmp_player[MAX_SIZE_FILE_NAME];
    memset(tmp_player, 0, MAX_SIZE_FILE_NAME);
    for(i = 0 ; i<=strlen(player_name) ; i++)
        tmp_player[i] = player_name[i];

    ptr_file_save = fopen(fileSave, "rb+");
    if(ptr_file_save == NULL){

        printf("Failed to open file %s\n", fileSave);
        exit(0);
    }
    fseek(ptr_file_save, 0, SEEK_SET);
    while( !nameFound && go == 1  )
    {
        memset(tmp, 0, MAX_SIZE_FILE_NAME);
        for(i  = 0 ; i<strlen(player_name) ; i++)
            go = fread(&tmp[i], sizeof(char), 1, ptr_file_save);

        if(strcmp(tmp, player_name) == 0)
        {
            nameFound = 1;
            fseek(ptr_file_save, MAX_SIZE_FILE_NAME  - strlen(player_name), SEEK_CUR);
            go = 0;

        }
        else if (go==1)
        {
            fseek(ptr_file_save, MAX_SIZE_FILE_NAME +4*sizeof(int) - strlen(player_name), SEEK_CUR);
        }
    }
    if(!nameFound)
    {
        printf("Failed to load player %s, save not found", player_name);
        exit(0);
    }
    fread(&player->levelMax, sizeof(int), 1, ptr_file_save);
    fread(&player->nbProjectile, sizeof(int), 1, ptr_file_save);
    fread(&player->nbLifes, sizeof(int), 1, ptr_file_save);
    fread(&player->nbCoins, sizeof(int), 1, ptr_file_save);

    fclose(ptr_file_save);

}


int savePlayer(char fileSave[MAX_SIZE_FILE_NAME], char player_name[MAX_SIZE_FILE_NAME], Player *player)
{
    FILE *ptr_file_save;
    int nameFound = 0, i, go = 1;
    char tmp[MAX_SIZE_FILE_NAME];
    char tmp_player[MAX_SIZE_FILE_NAME];
    memset(tmp_player, 0, MAX_SIZE_FILE_NAME);
    for(i = 0 ; i<=strlen(player_name) ; i++)
        tmp_player[i] = player_name[i];

    ptr_file_save = fopen(fileSave, "rb+");
    if(ptr_file_save == NULL){

        printf("Failed to open file %s\n", fileSave);
        exit(0);
    }
    fseek(ptr_file_save, 0, SEEK_SET);
    while( !nameFound && go == 1  )
    {
        memset(tmp, 0, MAX_SIZE_FILE_NAME);
        for(i  = 0 ; i<strlen(player_name) ; i++)
            go = fread(&tmp[i], sizeof(char), 1, ptr_file_save);

        if(strcmp(tmp, player_name) == 0)
        {
            nameFound = 1;
            fseek(ptr_file_save, MAX_SIZE_FILE_NAME  - strlen(player_name), SEEK_CUR);
            go = 0;

        }
        else if (go==1)
        {
            fseek(ptr_file_save, MAX_SIZE_FILE_NAME +4*sizeof(int) - strlen(player_name), SEEK_CUR);
        }
    }
    if(!nameFound)
    {
        fwrite(tmp_player, MAX_SIZE_FILE_NAME, 1, ptr_file_save);

    }
    fwrite(&player->levelMax, sizeof(int), 1, ptr_file_save);
    fwrite(&player->nbProjectile, sizeof(int), 1, ptr_file_save);
    fwrite(&player->nbLifes, sizeof(int), 1, ptr_file_save);
    fwrite(&player->nbCoins, sizeof(int), 1, ptr_file_save);

    fclose(ptr_file_save);

    return 1;
}


void save(SDL_Surface *screen, char fileSave[MAX_SIZE_FILE_NAME], char player_name[MAX_SIZE_FILE_NAME], Player *player, int *go)
{
    SDL_Rect posText, posWait;
    SDL_Surface *waiting;
    char choice[1];
    char tmp[MAX_SIZE_FILE_NAME];
    int ret = 0;
    Input in;
    memset(&in, 0, sizeof(in));
    choice[0]= 32;
    waiting = imageLoadAlpha("sprites/Background/menu_background.png");
    posWait.x = 0;
    posWait.y = 0;
    SDL_BlitSurface(waiting, NULL, screen, &posWait);

    posText.x = -1;
    posText.y = 250;
    sprintf(tmp, "Do you really want to save the progress of");
    printText(screen, &posText, tmp, 0, 0, 0, "polices/PressStart2P.ttf", 30, 1);
    posText.x = -1;
    posText.y = 300;
    sprintf(tmp, "%s (y/n) ?", player_name);
    printText(screen, &posText, tmp, 0, 0, 0, "polices/PressStart2P.ttf", 30, 1);

    posText.x = -1;
    posText.y = 350;
    captureText(screen, posText, choice, 1, 0, 0, 0, "polices/PressStart2P.ttf", 30, go, &ret);

    if(choice[0] == 'n')
    {
        sprintf(tmp, "Saving aborted  -  Press Enter to continue");
    }
    else if(choice[0] == 'y')
    {
        if(savePlayer(fileSave, player_name, player))
            sprintf(tmp, "Player %s progress saved  -  Press Enter to continue", player_name);
        else
            sprintf(tmp, "Error while saving the progress  -  Press Enter to continue");
    }

    ret = 0;
    in.key[SDLK_RETURN] = 0;
    while(!ret && *go)
    {
        posText.x = -1;
        posText.y = 450;
        printText(screen, &posText, tmp, 0, 0, 0, "../Super_Martin/polices/PressStart2P.ttf", 25, 1);
        SDL_Flip(screen);
        updateWaitEvents(&in, NULL);
        if(in.key[SDLK_RETURN])
        {
            ret = 1;
            in.key[SDLK_RETURN] = 0;
        }
    }
    SDL_FreeSurface(waiting);
}

void deletePlayer(SDL_Surface *screen, char fileSave[MAX_SIZE_FILE_NAME], char player_name[MAX_SIZE_FILE_NAME])
{
    FILE *ptr_file_save;
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int previous_time=0;
    int current_time=0;
    int i;
    int text_size;
    char confirmation[MAX_SIZE_FILE_NAME], deleted[MAX_SIZE_FILE_NAME], pressEnter[MAX_SIZE_FILE_NAME], playerPath[MAX_SIZE_FILE_NAME];
    char **player_list;
    int nb_player;
    int event_appear = 0;
    sprintf(playerPath, "configuration/%s.conf", player_name);
    Input in;

    SDL_Rect posText={0,0,0,0};
    sprintf(confirmation, "%s ? (y/n)", player_name);
    sprintf(pressEnter, "Press Enter to go back to the menu");
    sprintf(deleted, " ");

    /*  Waiting screen */

    waiting = imageLoadAlpha("../Super_Martin/sprites/Background/menu_background.png");
    posWait.x = 0;
    posWait.y = 0;

    /*  Text size */

    text_size = 25;

    /*  Initialization of the structure input */

    memset(&in,0,sizeof(in));

    while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN])
    {
        updateWaitEvents(&in, NULL);

        waitFPS(&previous_time,&current_time);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);
        posText.x = -1; // Center the text
        posText.y = 250;
        printText(screen, &posText, "Do you really want to delete the player :", 0, 0, 0, "../Super_Martin/polices/PressStart2P.ttf", text_size, 1);
        posText.x = -1;
        posText.y = 300;
        printText(screen, &posText, confirmation, 0, 0, 0, "../Super_Martin/polices/PressStart2P.ttf", text_size, 1);
        updateEvents(&in, NULL);
        if(in.key[SDLK_y])
        {
            in.key[SDLK_y] = 0;
            remove(playerPath);
            player_list = readLevelFile("save/players", &nb_player);
            ptr_file_save = fopen("save/players", "w+");

            if(ptr_file_save == NULL){

                fprintf(stderr, "Failed to open file /save/players\n");
                exit(1);
            }

            fseek(ptr_file_save, 0, SEEK_SET);
            fprintf(ptr_file_save, "%d\n", nb_player-1);
            for(i = 0; i < nb_player-1 ; i++)
            {
                if(strcmp(player_name, player_list[i]) != 0)
                {
                fseek(ptr_file_save, 0, SEEK_END);
                fprintf(ptr_file_save, "%s\n", player_list[i]);
                }
            }
            sprintf(deleted, "The player %s has been deleted", player_name);
            closeFile(ptr_file_save);
            nb_player -= 1;
            closeLevelList(player_list,nb_player);
            event_appear = 1;

        }
        else if(in.key[SDLK_n])
        {
            in.key[SDLK_n] = 0;
            event_appear = 1;
        }

        if(event_appear)
        {
            posText.x = -1;
            posText.y = 400;
            printText(screen, &posText, deleted, 0, 0, 0, "../Super_Martin/polices/PressStart2P.ttf", text_size, 1);
            posText.x = -1;
            posText.y = 450;
            printText(screen, &posText, pressEnter, 0, 0, 0, "../Super_Martin/polices/PressStart2P.ttf", text_size, 1);
        }

        SDL_Flip(screen);
    }
    SDL_FreeSurface(waiting);
}
