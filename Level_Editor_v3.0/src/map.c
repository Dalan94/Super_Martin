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
    SDL_Surface *tile;
    SDL_Rect posTile, posTileSet, curs;
    int i,j,minx,maxx,nbRow;

    posTile.h = posTile.w = posTileSet.h = posTileSet.w = TILE_SIZE;

    minx = m->xScroll/TILE_SIZE-1;
    maxx = (m->xScroll + m->screenWidth)/TILE_SIZE+1;
    nbRow = m->screenHeight/TILE_SIZE;

    tile = imageLoadAlpha(tileset);

     for(i=minx;i<maxx;i++){
        for(j=0;j<nbRow;j++){
            posTile.x = (i+1)*TILE_SIZE-m->xScroll;
            posTile.y = j*TILE_SIZE;
            posTileSet.x = m->lvl->map[j][i] % TILESET_LAST * TILE_SIZE;
            posTileSet.y = m->lvl->map[j][i] / TILESET_LAST * TILE_SIZE;

            if(i>=0 && i<m->lvl->width)
            {
                SDL_BlitSurface(tile,&posTileSet,screen,&posTile);
            }
        }
    }
    curs.x = cursor->x;
    curs.y = cursor->y;
    posTileSet.y = cursor->tileID / TILESET_LAST * TILE_SIZE;
    posTileSet.x = cursor->tileID % TILESET_LAST * TILE_SIZE;
    SDL_BlitSurface(tile,&posTileSet,screen,&curs);
    SDL_FreeSurface(tile);

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
