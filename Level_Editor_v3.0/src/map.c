/*!
 * \file map.c
 * \brief Management of the map
 * \author Xavier COPONET, Glenn HERROU
 * \date 2014-05-18
 */

#include "map.h"

void updateScreenMap(SDL_Surface *screen, Map *m, char *tileset, Cursor *cursor){
    SDL_Surface *tile, *enemy, *tree, *flower, *cloud, *platform, *platformH, *platformV, *canonL,*canonR,*canonB;
    SDL_Rect posTile, posTileSet, posTree, curs;
    int i,j,minx,maxx,nbRow;
    float y_off, x_off;

    posTile.h = posTile.w = posTileSet.h = posTileSet.w = TILE_SIZE;

    minx = m->xScroll/TILE_SIZE-1;
    maxx = (m->xScroll + m->screenWidth)/TILE_SIZE+1;
    nbRow = m->screenHeight/TILE_SIZE;

    tile = imageLoadAlpha(tileset);
    enemy = imageLoadAlpha("../Super_Martin/sprites/Characters/witch_doctor.png");
    cloud = imageLoadAlpha("../Super_Martin/sprites/cloud.png");
    flower = imageLoadAlpha("../Super_Martin/sprites/flower.png");
    platform = imageLoadAlpha("../Super_Martin/sprites/moving_platform.png");
    platformH = imageLoadAlpha("../Super_Martin/sprites/platformH.png");
    platformV = imageLoadAlpha("../Super_Martin/sprites/platformV.png");
    canonR = imageLoadAlpha("sprites/canonR.png");
    canonL = imageLoadAlpha("sprites/canonL.png");
    canonB = imageLoadAlpha("sprites/canonB.png");

    if(!(strcmp(tileset, "../Super_Martin/sprites/tileSet_Snow.png")))
    {
        x_off = 1.25;
        y_off = 5.5;
        posTree.h = posTile.h = 104;
        posTree.w = posTile.w = 55;
        tree = imageLoadAlpha("../Super_Martin/sprites/snow_tree.png");
    }
    else if(!(strcmp(tileset, "../Super_Martin/sprites/tileSet_Beach.png")))
    {
        x_off = 1.25;
        y_off = 5.5;
        posTree.h = posTile.h = 104;
        posTree.w = posTile.w = 96;
        tree = imageLoadAlpha("../Super_Martin/sprites/beach_tree.png");
    }
    else
    {
        x_off = 2;
        y_off = 1.85;
        posTree.h = posTile.h = 65;
        posTree.w = posTile.w = 96;
        tree = imageLoadAlpha("../Super_Martin/sprites/grassland_tree.png");

    }

     for(i=minx;i<maxx;i++){
        for(j=0;j<nbRow;j++){

            if(i>=0 && i<m->lvl->width)
            {
                if(m->lvl->map[j][i] == 'T')
                {
                    posTile.x = (i+1-x_off)*TILE_SIZE-m->xScroll;
                    posTile.y = (j-y_off)*TILE_SIZE;
                    posTree.x = posTree.y = 0;
                    posTile.h = posTree.h;
                    posTile.w = posTree.w;
                    SDL_BlitSurface(tree, &posTree, screen, &posTile);
                }
                else if(m->lvl->map[j][i] == 'E')
                {
                    posTile.x = (i+1)*TILE_SIZE-m->xScroll;
                    posTile.y = (j-0.85)*TILE_SIZE;
                    posTileSet.h = posTile.h = 29;
                    posTileSet.w = posTile.w = 35;
                    SDL_BlitSurface(enemy, &posTileSet, screen, &posTile);
                }
                else if(m->lvl->map[j][i] == 'A' || m->lvl->map[j][i] == 'B')
                {
                    posTile.x = (i)*TILE_SIZE-m->xScroll;
                    posTile.y = (j-0.85)*TILE_SIZE;
                    posTileSet.h = posTile.h = 16;
                    posTileSet.w = posTile.w = 64;
                    SDL_BlitSurface(platform, &posTileSet, screen, &posTile);
                }
                else if(m->lvl->map[j][i] == 'H')
                {
                    posTile.x = (i+1)*TILE_SIZE-m->xScroll;
                    posTile.y = j*TILE_SIZE;
                    posTile.h = posTile.w = posTileSet.h = posTileSet.w = TILE_SIZE;
                    posTileSet.x = HEART % TILESET_SIZE * TILE_SIZE;
                    posTileSet.y = HEART / TILESET_SIZE * TILE_SIZE;
                    SDL_BlitSurface(tile,&posTileSet,screen,&posTile);
                }
                else if(m->lvl->map[j][i] == 'L')
                {
                    posTile.x = (i+1)*TILE_SIZE-m->xScroll;
                    posTile.y = j*TILE_SIZE;
                    posTile.h = posTile.w = posTileSet.h = posTileSet.w = TILE_SIZE;
                    posTileSet.x = ADDLIFE % TILESET_SIZE * TILE_SIZE;
                    posTileSet.y = ADDLIFE / TILESET_SIZE * TILE_SIZE;
                    SDL_BlitSurface(tile,&posTileSet,screen,&posTile);
                }
                else if(m->lvl->map[j][i] == 'N')
                {
                    posTile.x = (i+1-4)*TILE_SIZE-m->xScroll;
                    posTile.y = (j-2.5)*TILE_SIZE;
                    posTileSet.h = posTile.h = 80;
                    posTileSet.w = posTile.w = 144;
                    SDL_BlitSurface(cloud, &posTileSet, screen, &posTile);
                }
                else if(m->lvl->map[j][i] == 'P')
                {
                    posTile.x = (i+1)*TILE_SIZE-m->xScroll;
                    posTile.y = (j-0.9375)*TILE_SIZE;
                    posTileSet.h = posTile.h = 30;
                    posTileSet.w = posTile.w = 30;
                    SDL_BlitSurface(flower, &posTileSet, screen, &posTile);
                }
                else if(m->lvl->map[j][i] == 'F')
                {
                    posTile.x = (i+1)*TILE_SIZE-m->xScroll;
                    posTile.y = j*TILE_SIZE;
                    posTile.h = posTile.w = posTileSet.h = posTileSet.w = TILE_SIZE;
                    SDL_BlitSurface(canonL, NULL, screen, &posTile);
                }
                else if(m->lvl->map[j][i] == 'G')
                {
                    posTile.x = (i+1)*TILE_SIZE-m->xScroll;
                    posTile.y = j*TILE_SIZE;
                    posTile.h = posTile.w = posTileSet.h = posTileSet.w = TILE_SIZE;
                    SDL_BlitSurface(canonR, NULL, screen, &posTile);
                }
                else if(m->lvl->map[j][i] == 'D')
                {
                    posTile.x = (i+1)*TILE_SIZE-m->xScroll;
                    posTile.y = j*TILE_SIZE;
                    posTile.h = posTile.w = posTileSet.h = posTileSet.w = TILE_SIZE;
                    SDL_BlitSurface(canonB, NULL, screen, &posTile);
                }
                else
                {
                    posTile.x = (i+1)*TILE_SIZE-m->xScroll;
                    posTile.y = j*TILE_SIZE;
                    posTile.h = posTile.w = posTileSet.h = posTileSet.w = TILE_SIZE;
                    if(m->lvl->map[j][i] == 'C')
                    {
                        posTileSet.x = 10 % TILESET_SIZE * TILE_SIZE;
                        posTileSet.y = 10 / TILESET_SIZE * TILE_SIZE;
                    }
                    else
                    {
                        posTileSet.x = m->lvl->map[j][i] % TILESET_SIZE * TILE_SIZE;
                        posTileSet.y = m->lvl->map[j][i] / TILESET_SIZE * TILE_SIZE;
                    }
                    SDL_BlitSurface(tile,&posTileSet,screen,&posTile);
                }
            }
        }
    }

    if(cursor->tileID == TREE)
    {
        curs.x = cursor->x - (x_off * TILE_SIZE);
        curs.y = cursor->y - (y_off * TILE_SIZE);
        posTree.x = posTree.y = 0;
        posTileSet.h = curs.h = 104;
        posTileSet.w = curs.w = 96;
        SDL_BlitSurface(tree, &posTree, screen, &curs);
    }
    else if(cursor->tileID == ENEMY)
    {
        curs.x = cursor->x - TILE_SIZE / 2;
        curs.y = cursor->y - 0.85*TILE_SIZE;
        posTileSet.x = posTileSet.y = 0;
        posTileSet.h = curs.h = 29;
        posTileSet.w = curs.w = 35;
        SDL_BlitSurface(enemy, &posTileSet, screen, &curs);
    }
    else if(cursor->tileID == PLATFORMV)
    {
        curs.x = cursor->x - 2.2 * TILE_SIZE;
        curs.y = cursor->y - 2 * TILE_SIZE;
        posTileSet.x = posTileSet.y = 0;
        posTileSet.h = curs.h = 64;
        posTileSet.w = curs.w = 80;
        SDL_BlitSurface(platformV, &posTileSet, screen, &curs);
    }
    else if(cursor->tileID == PLATFORMH)
    {
        curs.x = cursor->x - 1.2 * TILE_SIZE;
        curs.y = cursor->y - 2 * TILE_SIZE;
        posTileSet.x = posTileSet.y = 0;
        posTileSet.h = curs.h = 32;
        posTileSet.w = curs.w = 64;
        SDL_BlitSurface(platformH, &posTileSet, screen, &curs);
    }
    else if(cursor->tileID == FLOWER)
    {
        curs.x = cursor->x - TILE_SIZE / 2;
        curs.y = cursor->y - 0.9375*TILE_SIZE;
        posTileSet.x = posTileSet.y = 0;
        posTileSet.h = curs.h = 30;
        posTileSet.w = curs.w = 30;
        SDL_BlitSurface(flower, &posTileSet, screen, &curs);
    }
    else if(cursor->tileID == CLOUD)
    {
        curs.x = cursor->x - 4 * TILE_SIZE;
        curs.y = cursor->y - 2.5 * TILE_SIZE;
        posTileSet.x = posTileSet.y = 0;
        posTileSet.h = curs.h = 80;
        posTileSet.w = curs.w = 144;
        SDL_BlitSurface(cloud, &posTileSet, screen, &curs);
    }
    else if(cursor->tileID == CANON_L)
    {
        curs.x = cursor->x;
        curs.y = cursor->y;
        curs.h = curs.w = TILE_SIZE;
        SDL_BlitSurface(canonL, NULL, screen, &curs);
    }
    else if(cursor->tileID == CANON_R)
    {
        curs.x = cursor->x;
        curs.y = cursor->y;
        curs.h = curs.w = TILE_SIZE;
        SDL_BlitSurface(canonR, NULL, screen, &curs);
    }
    else if (cursor->tileID == CANON_B)
    {
        curs.x = cursor->x;
        curs.y = cursor->y;
        curs.h = curs.w = TILE_SIZE;
        SDL_BlitSurface(canonB, NULL, screen, &curs);
    }
    else
    {
        curs.x = cursor->x;
        curs.y = cursor->y;
        curs.h = curs.w = TILE_SIZE;
        posTileSet.y = cursor->tileID / TILESET_SIZE * TILE_SIZE;
        posTileSet.x = cursor->tileID % TILESET_SIZE * TILE_SIZE;
        SDL_BlitSurface(tile,&posTileSet,screen,&curs);
    }
    SDL_FreeSurface(tile);
    SDL_FreeSurface(tree);
    SDL_FreeSurface(enemy);
    SDL_FreeSurface(cloud);
    SDL_FreeSurface(flower);
    SDL_FreeSurface(canonL);
    SDL_FreeSurface(canonR);
    SDL_FreeSurface(canonB);

}

Map *initMap(SDL_Surface *screen,char *level_name){
    Map *m;

    m = (Map *)malloc(sizeof(Map));
    if (m == NULL){
        perror("allocation error");
        exit(errno);
    }
    m->lvl=openLevel(level_name);
    m->screenHeight = screen->h;
    m->screenWidth = screen->w;
    m->xScroll = 20;

    return m;
 }

void fillLine(Map *m, int line, int column, char tileID)
{
    int i = column;
    if(tileID == VOID || tileID == GROUND+1 || tileID == GROUND+4)
    {
        while(i < ((m->xScroll + m->screenWidth)/(TILE_SIZE)) && (m->lvl->map[line][i] == VOID || m->lvl->map[line][i] == GROUND+1 || m->lvl->map[line][i] == GROUND+4 || m->lvl->map[line][i] == tileID))
        {
            m->lvl->map[line][i] = tileID;
            i++;
        }
        i = column;
        while(i >= m->xScroll/TILE_SIZE && (m->lvl->map[line][i] == VOID || m->lvl->map[line][i] == GROUND+1 || m->lvl->map[line][i] == GROUND+4 || m->lvl->map[line][i] == tileID))
        {
            m->lvl->map[line][i] = tileID;
            i--;
        }
    }
}

void fillColumn(Map *m, int line, int column, char tileID)
{
    int i = line;
    if(tileID == VOID || (tileID != GROUND && tileID != GROUND+2 && tileID < COIN))
    {
        while(i < NB_TILES_Y && (m->lvl->map[i][column] == VOID || m->lvl->map[i][column] == tileID || (m->lvl->map[i][column] > GROUND+2 && m->lvl->map[i][column] < COIN)))
        {
            m->lvl->map[i][column] = tileID;
            i++;
        }
        i = line;
        while(i >= 0 && (m->lvl->map[i][column] == VOID || m->lvl->map[i][column] == tileID || (m->lvl->map[i][column] > GROUND+2 && m->lvl->map[i][column] < COIN)))
        {
            m->lvl->map[i][column] = tileID;
            i--;
        }
    }
}

void fillRect(Map *m, int line, int column, char tileID)
{
    int i = line;
    if(tileID == VOID || tileID == GROUND+4)
    {
        while(i < NB_TILES_Y && (m->lvl->map[i][column] == VOID || m->lvl->map[i][column] == GROUND+4))
        {
            fillLine(m, i, column, tileID);
            i++;
        }
        i = line;
        while(i >= 0 && (m->lvl->map[i][column] == VOID || m->lvl->map[i][column] == GROUND+4))
        {
            fillLine(m, i, column, tileID);
            i--;
        }
    }
}

void displayHelp(SDL_Surface *screen, SDLKey *kc)
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int i, ret = 0, nb_key = 18;
    int text_size;
    char key_names[18][MAX_LENGTH_FILE_NAME]={"Left","Right","Save","Reset", "Enemy", "Tree", "Flower", "Cloud", "Ground", "Coin", "Rock", "Spring", "Blank", "Platform", "Help", "Fill Line", "Fill Column", "Fill Rect"};
    char key[MAX_LENGTH_FILE_NAME];


    Input in;

    SDL_Rect posText={0,0,0,0};

    /*  waiting screen */

    waiting = imageLoad("../Super_Martin/sprites/game-over.jpg");
    posWait.x = posWait.y = 0;
    SDL_SetAlpha(waiting, SDL_SRCALPHA, 200);
    SDL_BlitSurface(waiting,NULL,screen,&posWait);
    memset(&in,0,sizeof(in));



    while(!ret)
    {
        updateWaitEvents(&in);
        if(in.key[SDLK_ESCAPE] || in.key[SDLK_RETURN] || in.key[kc[14]] || in.quit)
            ret = 1;
        for (i=0 ; i < nb_key ; i++)
        {

            text_size= (screen->h -300)/ (min(nb_key, OPTIONS_PER_COLUMN));
            if (text_size > 35)
                text_size=35;
            if(i>= 2*OPTIONS_PER_COLUMN)
            {
                posText.x = 750;
                posText.y = 150 +screen->h / (1.5*(1+OPTIONS_PER_COLUMN)) * (i+1-2*OPTIONS_PER_COLUMN) - text_size;
            }
            else if(i>=OPTIONS_PER_COLUMN)
            {
                posText.x = 450;
                posText.y = 150 +screen->h / (1.5*(1+OPTIONS_PER_COLUMN)) * (i+1-OPTIONS_PER_COLUMN) - text_size;
            }
            else
            {
                posText.x = 150;
                posText.y = 150 + screen->h / (1.5*(1+min(OPTIONS_PER_COLUMN, nb_key))) * (i+1) - text_size;
            }

            switch(i)
            {
                case 15 :
                    sprintf(key,"%s : CTRL + left click",key_names[i]);
                    break;
                case 16 :
                    sprintf(key,"%s : SHIFT + left click",key_names[i]);
                    break;
                case 17 :
                    sprintf(key,"%s : SPACE + left click",key_names[i]);
                    break;
                default :
                    sprintf(key,"%s : %s",key_names[i],SDL_GetKeyName(kc[i]));
                    break;
            }


            printText(screen,&posText,key,255,60,30,"../Super_Martin/polices/PressStart2P.ttf",text_size,1);
        }

        SDL_Flip(screen);
    }
}

void saveMap(SDL_Surface *screen, Map *m){

    SDL_Surface *waiting = NULL;
    SDL_Rect posWait;
    char level_name[MAX_LENGTH_FILE_NAME];
    char level_name_tmp[MAX_LENGTH_FILE_NAME];
    char choice[1];
    char tmp[MAX_LENGTH_FILE_NAME];
    char tmp2[MAX_LENGTH_FILE_NAME];
    FILE *ptr_file_level;
    int level_number;
    int nb_lvl;
    char **level_list;
    int i, j;
    int incr;
    int wrong_name = 1;
    SDL_Rect posText={0,0,0,0};
    int text_size = 30;
    int go = 1;
    int ret = 1, ret2 = 0;
    choice[0]= 32;
    Input in;

    memset(&in, 0, sizeof(in));

    level_list = readLevelFile(&level_number);
    nb_lvl = level_number;
    waiting = imageLoad("../Super_Martin/sprites/game-over.jpg");
    posWait.x = posWait.y = 0;
    SDL_SetAlpha(waiting, SDL_SRCALPHA, 200);
    SDL_BlitSurface(waiting,NULL,screen,&posWait);

    posText.x = -1;
    posText.y = 150;
    printText(screen, &posText, "Enter the name of the level : ", 186, 38, 18, "../Super_Martin/polices/PressStart2P.ttf", text_size, 1);
    SDL_Flip(screen);

    /*  Save the screen to clear the display of the level_name  later */

    level_name_tmp[0] = 32;

    /*  Main loop */

    while(wrong_name)
    {
        memset(tmp, 0, sizeof(tmp));
        tmp[0] = ' ';
        memset(level_name_tmp, 0, sizeof(tmp));
        incr = 1;
        wrong_name = 0;

        posText.x = -1;
        posText.y = 220;

        captureText(screen, posText, level_name_tmp, MAX_LENGTH_FILE_NAME, 186, 38, 18, "../Super_Martin/polices/PressStart2P.ttf", text_size, &go);

        ret = 1;

        /*  Manage the file name conflicts */

        for (j=0 ; j<level_number && ret && go; j++)
        {
            if (!strcmp(level_name_tmp, level_list[j]))
            {
                posText.x = -1;
                posText.y = 300;
                text_size = 22;
                printText(screen, &posText, "File already exists. Do you want to continue ? (y/n)", 186, 38, 18, "../Super_Martin/polices/PressStart2P.ttf", text_size, 1);

                posText.x = -1;
                posText.y = 370;

                captureText(screen, posText, choice, 1, 186, 38, 18, "../Super_Martin/polices/PressStart2P.ttf", text_size, &go);

                if(choice[0] == 'n')
                {
                    sprintf(tmp, "Saving aborted  -  Press Enter to continue");
                    ret = 0;
                }
                else if(choice[0] == 'y')
                {
                    sprintf(tmp, "Map %s saved  -  Press Enter to continue", level_name_tmp);
                    incr = 0;
                    ret = 1;
                }
            }
        }
        if(choice[0] == ' ' && go)
        {
            sprintf(tmp, "Map %s saved  -  Press Enter to continue", level_name_tmp);
            ret = 1;
        }
    }
    nb_lvl += incr;
    /*  Update the file 'level' containing the level list */

    if(go && ret)
    {
        memset(tmp2, 0, sizeof(tmp2));
        tmp2[0] = ' ';
        ptr_file_level = fopen("../Super_Martin/level/level", "w+");
        choice[0] = ' ';
        if(ptr_file_level == NULL)
        {
            printf("Failed to open file /level/level\n");
            exit(1);
        }
        fseek(ptr_file_level, 0, SEEK_SET);
        fprintf(ptr_file_level, "%d\n", nb_lvl);
        while((choice[0] <= 0 || choice[0]>= 10))
        {
            posText.x = -1;
            posText.y = 420;
            text_size = 22;
            sprintf(tmp2, "Choose the position in the map list for %s :", level_name_tmp);
            printText(screen, &posText, tmp2, 186, 38, 18, "../Super_Martin/polices/PressStart2P.ttf", text_size, 1);
            posText.x = -1;
            posText.y = 470;
            captureText(screen, posText, choice, 1, 186, 38, 18, "../Super_Martin/polices/PressStart2P.ttf", text_size, &go);
            choice[0] -= 48;
        }

        for(i = 0 ; i <= nb_lvl ; )
        {
            fseek(ptr_file_level, 0, SEEK_END);
            if(i== (choice[0]-1) && ret)
            {


                /*if(strcmp(level_name_tmp, level_list[i]) != 0)
                    fprintf(ptr_file_level, "%s\n", level_list[i]);*/
                fprintf(ptr_file_level, "%s\n", level_name_tmp);
                ret=0;
            }
            else if(i<nb_lvl-1 && strcmp(level_name_tmp, level_list[i+ret2]) != 0)
            {
                fprintf(ptr_file_level, "%s\n", level_list[i+ret2]);
                i++;
            }
            else if(i<nb_lvl-1 && strcmp(level_name_tmp, level_list[i]) == 0)
            {
                fprintf(ptr_file_level, "%s\n", level_list[i+1]);
                ret2 = 1;
                i++;
            }
            else
                i++;


        }
        if(choice[0] > (nb_lvl))
        {
            fseek(ptr_file_level, 0, SEEK_END);
            fprintf(ptr_file_level, "%s\n", level_name_tmp);
        }


        closeFile(ptr_file_level);

        /*  Write the level in the file */

        sprintf(level_name,"../Super_Martin/level/%s.lvl",level_name_tmp);


        writeLevel(level_name, m->lvl);
    }
    ret = 1;
    in.key[SDLK_RETURN] = 0;
    while(ret && go)
    {
        posText.x = -1;
        posText.y = 520;
        text_size = 25;
        printText(screen, &posText, tmp, 186, 38, 18, "../Super_Martin/polices/PressStart2P.ttf", text_size, 1);
        SDL_Flip(screen);
        updateWaitEvents(&in);
        if(in.key[SDLK_RETURN])
        {
            ret = 0;
            in.key[SDLK_RETURN] = 0;
        }

    }

    /*  Freeing of allocated spaces */

    closeLevelList(level_list, level_number);
    SDL_FreeSurface(waiting);
}

void deleteMap(SDL_Surface *screen, char *map_name, char *map_path)
{
    FILE *ptr_file_level;
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int previous_time=0;
    int current_time=0;
    int i;
    int text_size;
    char confirmation[MAX_LENGTH_FILE_NAME], deleted[MAX_LENGTH_FILE_NAME], pressEnter[MAX_LENGTH_FILE_NAME];
    char **level_list;
    int nb_lvl;
    int event_appear = 0;

    Input in;

    SDL_Rect posText={0,0,0,0};
    sprintf(confirmation, "%s ? (y/n)", map_name);
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
        updateWaitEvents(&in);

        waitFPS(&previous_time,&current_time);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);
        posText.x = -1; // Center the text
        posText.y = 250;
        printText(screen, &posText, "Do you really want to delete the map :", 0, 0, 0, "../Super_Martin/polices/PressStart2P.ttf", text_size, 1);
        posText.x = -1;
        posText.y = 300;
        printText(screen, &posText, confirmation, 0, 0, 0, "../Super_Martin/polices/PressStart2P.ttf", text_size, 1);
        updateEvents(&in);
        if(in.key[SDLK_y])
        {
            in.key[SDLK_y] = 0;
            remove(map_path);
            level_list = readLevelFile(&nb_lvl);
            ptr_file_level = fopen("../Super_Martin/level/level", "w+");

            if(ptr_file_level == NULL){

                printf("Failed to open file /level/level\n");
                exit(1);
            }

            fseek(ptr_file_level, 0, SEEK_SET);
            fprintf(ptr_file_level, "%d\n", nb_lvl-1);
            for(i = 0; i < nb_lvl ; i++)
            {
                if(strcmp(map_name, level_list[i]) != 0)
                {
                fseek(ptr_file_level, 0, SEEK_END);
                fprintf(ptr_file_level, "%s\n", level_list[i]);
                }
            }
            sprintf(deleted, "The map %s has been deleted", map_name);
            closeFile(ptr_file_level);
            nb_lvl -= 1;
            closeLevelList(level_list,nb_lvl);
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

void extendMap(Map *m)
{
    int i, j;
    m->lvl->width += 100;

    for (i=0 ; i<m->lvl->height ; i++)
    {
        if ((m->lvl->map[i]=(unsigned char *)realloc(m->lvl->map[i], m->lvl->width*sizeof(unsigned char)+1)) == NULL)
        {
            printf("\nProbleme allocation memoire\n");
            perror("");
            exit(0);
        }
        for(j=m->lvl->width-99 ; j<=m->lvl->width; j++)
        {
            m->lvl->map[i][j] = 0;
        }
    }
}

void resetMap(Map *m){

    int i,j;
    for(i=0 ; i < m->lvl->height ; i++)
    {
        for (j=0 ; j < m->lvl->width ; j++)
            m->lvl->map[i][j]=0;
    }
}

void freeMap(Map *m){
    closeLevel(m->lvl);
    free((void *)m);
}
