#include "player.h"

int newPlayer(SDL_Surface *screen,char player_name[MAX_SIZE_FILE_NAME],Sound *s,int *go)
{
    SDL_Surface *waiting;
    SDL_Rect posText, posWait;
    int text_size = 40;
    int i, incr, ret = 0;
    int wrong_player = 1;
    int nb_players;
    char **player_list;
    char tmp[MAX_SIZE_FILE_NAME];
    FILE *ptr_file_player;
    char choice[1];
    int res;

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
        memset(player_name, 0, sizeof(player_name));
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
                posText.y = 280;
                captureText(screen, posText, player_name, MAX_SIZE_FILE_NAME, 0, 0, 0, "polices/PressStart2P.ttf", text_size, go, &ret);
            }
        }
        ret = 0;
        for(i = 0; !ret && *go && i < nb_players-1; i++)
        {
            if(!(strcmp(player_name, player_list[i])))
            {
                posText.x = -1;
                posText.y = 380;
                text_size = 20;
                sprintf(tmp, "%s already exists. Do you want to continue (y/n) ?", player_name);
                printText(screen, &posText, tmp, 0, 0, 0, "polices/PressStart2P.ttf", text_size, 1);
                posText.x = -1;
                posText.y = 420;
                text_size = 20;
                sprintf(tmp, "The progression of %s will be erased ", player_name);
                printText(screen, &posText, tmp, 0, 0, 0, "polices/PressStart2P.ttf", text_size, 1);

                SDL_Flip(screen);
                posText.x = -1;
                posText.y = 480;
                text_size = 30;
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
        posText.y = 530;
        text_size = 25;
        printText(screen, &posText, tmp, 0, 0, 0, "../Super_Martin/polices/PressStart2P.ttf", text_size, 1);
        SDL_Flip(screen);
        updateWaitEvents(&in, NULL);
        if(in.key[SDLK_RETURN])
        {
            ret = 1;
            in.key[SDLK_RETURN] = 0;
        }
    }
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
    fread(&player->hpMax, sizeof(int), 1, ptr_file_save);
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
    //fread(tmp, sizeof(player_name), 1, ptr_file_save);
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
        //fseek(ptr_file_save, 0, SEEK_END);
        fwrite(tmp_player, MAX_SIZE_FILE_NAME, 1, ptr_file_save);

    }
    fwrite(&player->levelMax, sizeof(int), 1, ptr_file_save);
    fwrite(&player->hpMax, sizeof(int), 1, ptr_file_save);
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
    //sprintf(player->name,"%s", player_name);
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
