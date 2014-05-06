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

        printf("Failed to open file /level/level\n");
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
