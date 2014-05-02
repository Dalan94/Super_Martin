/*!
 * \file map.c
 * \brief loading and displaying the map
 * \author Xavier COPONET
 * \date 2014-03-18
 */

#include "map.h"

/**
 *\fn void updateScreenMap(SDL_Surface *screen, Map *m,char *tileset)
 *update and display the map
 *\param[in,out] screen of the game
 *\param[in] Map *m The map
 *\param[in] tileset lvl tileset
 */
void updateScreenMap(SDL_Surface *screen, Map *m, char *tileset, Cursor *cursor){
    SDL_Surface *tile, *enemy, *tree, *flower, *cloud;
    SDL_Rect posTile, posTileSet, posTree, curs;
    int i,j,minx,maxx,nbRow;
    float y_off, x_off;

    posTile.h = posTile.w = posTileSet.h = posTileSet.w = TILE_SIZE;
    //posTileSet.x = posTileSet.y = posTree.x = posTree.y = 0;

    minx = m->xScroll/TILE_SIZE-1;
    maxx = (m->xScroll + m->screenWidth)/TILE_SIZE+1;
    nbRow = m->screenHeight/TILE_SIZE;

    tile = imageLoadAlpha(tileset);
    enemy = imageLoadAlpha("../Super_Martin/sprites/Characters/witch_doctor.png");
    cloud = imageLoadAlpha("../Super_Martin/sprites/cloud.png");
    flower = imageLoadAlpha("../Super_Martin/sprites/flower.png");

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
                else
                {
                    posTile.x = (i+1)*TILE_SIZE-m->xScroll;
                    posTile.y = j*TILE_SIZE;
                    posTile.h = posTile.w = posTileSet.h = posTileSet.w = TILE_SIZE;
                    posTileSet.x = m->lvl->map[j][i] % TILESET_SIZE * TILE_SIZE;
                    posTileSet.y = m->lvl->map[j][i] / TILESET_SIZE * TILE_SIZE;
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

}

/**
 *\fn void scrolling(Map *m,int direction,float speed)
 *scroll the map
 *\param[in,out] map the lvl
 *\param[in] direction scrolling direction
 *\param[in] speed scrolling speed
 */
void scrolling(Map *m, int direction,float speed){
    switch (direction){
        case RIGHT:
            if(m->xScroll < (m->lvl->width+1)*TILE_SIZE-m->screenWidth)
                m->xScroll+= speed;
            break;

        case LEFT:
            if(m->xScroll > TILE_SIZE)
                m->xScroll-= speed;
            break;
        default: ;
    }
}

/**
 *\fn  Map *initMap(SDL_Surface *screen,char * level_name){
 *initialize the map
 *\param[in] screen game screen
 *\param[in] level_name lvl name
 *\return pointer on the map
 */
 Map *initMap(SDL_Surface *screen,char * level_name){
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

/**
  *\fn void saveMap(map *m)
  *Save the map in a new file and update the file 'level' containing the map list
  *\param[in] m The map to save
  */

void saveMap(Map *m){

    char level_name[MAX_LENGTH_FILE_NAME];
    char level_name_tmp[MAX_LENGTH_FILE_NAME];
    FILE *ptr_file_level;
    int level_number;
    char **level_list;
    int i;
    char choice;
    int incr;
    int wrong_name = 1;

    ptr_file_level = fopen("../Super_Martin/level/level", "r+");

    if(ptr_file_level == NULL){

        printf("Failed to open file /level/level\n");
        exit(1);
    }

    level_list = readLevelFile(&level_number);
    printf("Existing maps :\n");
    for(i=0;i<level_number;i++)
        printf("%s\n", level_list[i]);
    /*  Manage the file name conflicts */
    while(wrong_name){

        incr = 1;
        wrong_name = 0;
        printf("Enter the name of the level : ");
        fgets(level_name_tmp, sizeof(level_name_tmp), stdin);
        cleanString(level_name_tmp, stdin);
        for (i=0 ; i<level_number ; i++)
        {
            if (!strcmp(level_name_tmp, level_list[i])){

                printf("File already exists. Do you want to continue ? (y/n)");
                scanf("%c", &choice);
                if(choice == 'n'){
                    wrong_name = 1;
                }else{incr = 0;}
            clean_stdin();
            }

        }

    }
    /*  Update the file 'level' containing the level list */

    fseek(ptr_file_level, 0, SEEK_SET);
    fprintf(ptr_file_level, "%d", (level_number+incr));
    fseek(ptr_file_level, 0, SEEK_END);
    if(incr !=0){

        fprintf(ptr_file_level, "%s\n", level_name_tmp);
    }

    closeFile(ptr_file_level);
    printf("Map %s saved\n", level_name_tmp);
    /*  Write the level in the file */

    sprintf(level_name,"../Super_Martin/level/%s.lvl",level_name_tmp);


    writeLevel(level_name, m->lvl);

    closeLevelList(level_list, level_number);
}
/**
  *\fn void deleteMap(SDL_Surface *screen, char *map_name, char *map_path)
  *Delete a the map file and update the level list file
  *\param[in,out] screen The screen of the game
  *\param[in] map_name The name of the map to delete
  *\param[in] map_path The path to the file of the map to delete
  */

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

    waiting = imageLoadAlpha("../Super_Martin/sprites/Background/desert_hills_2.png");
    posWait.x = 0;
    posWait.y = 0;

    /*  Text size */

    text_size = 40;

    /*  Initialization of the structure input */

    memset(&in,0,sizeof(in));

    while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN])
    {
        updateWaitEvents(&in);

        waitFPS(&previous_time,&current_time);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);
        posText.x = -1; // Center the text
        posText.y = 150;
        printText(screen, &posText, "Do you really want to delete the map :", 0, 0, 0, "../Super_Martin/polices/ubuntu.ttf", text_size, 1);
        posText.x = -1;
        posText.y = 210;
        printText(screen, &posText, confirmation, 0, 0, 0, "../Super_Martin/polices/ubuntu.ttf", text_size, 1);
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
        posText.y = 300;
        printText(screen, &posText, deleted, 0, 0, 0, "../Super_Martin/polices/ubuntu.ttf", text_size, 1);
        posText.x = -1;
        posText.y = 350;
        printText(screen, &posText, pressEnter, 0, 0, 0, "../Super_Martin/polices/ubuntu.ttf", text_size, 1);
        }

        SDL_Flip(screen);
    }
    SDL_FreeSurface(waiting);
}


/**
  *\fn void extendMap(Map *m)
  *Extend the width of a map
  *\param[out] m The map to extend
  */

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
        for(j=m->lvl->width-99 ; j<m->lvl->width; j++)
        {
            m->lvl->map[i][j] = 0;
        }
    }
}



/**
  *\fn void reinitMap(map *m)
  *Fill a map with blank tiles. This function doesn't change the current map file.
  *\param[in,out] m The map to reinit
  */

void reinitMap(Map *m){

    int i,j;
    for(i=0 ; i < m->lvl->height ; i++)
    {
        for (j=0 ; j < m->lvl->width ; j++)
            m->lvl->map[i][j]=0;
    }
}
 /**
  *\fn void freeMap(map *m)
  *free memory allocated to the map
  *\param[in,out] m the map
  */
void freeMap(Map *m){
    closeLevel(m->lvl);
    free((void *)m);
}

void cleanString(const char *buffer, FILE *fp)
{
    char *p = strchr(buffer,'\n');
    if (p != NULL)
        *p = 0;
    else
    {
        int c;
        while ((c = fgetc(fp)) != '\n' && c != EOF);
    }
}

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
