/*!
 * \file game.c
 * \brief Contains the functions managing the maps
 * \author Xavier COPONET, Glenn HERROU
 * \date 2014-03-18
 */


#include "game.h"


/**
 *\fn void updateScreenMap(SDL_Surface *screen, Map *m,char *tileset)
 *Update the screen with the data of the map (ignore characters)
 *\param[in,out] screen The screen of the game
 *\param[in] Map *m The map
 *\param[in] tileset The tileset used to draw the level
 */
void updateScreenMap(SDL_Surface *screen, Map *m, char *tileset, Cursor *cursor){

    SDL_Surface *tile;
    SDL_Rect posTile, posTileSet, curs;
    int i,j;
    int minx, maxx, nbRow;

    posTile.h = posTile.w = posTileSet.h = posTileSet.w = curs.h = curs.w = TILE_SIZE;

    minx = m->xScroll/TILE_SIZE-1;
    maxx = (m->xScroll + m->screenWidth)/TILE_SIZE+1;
    nbRow = m->screenHeight/TILE_SIZE;

    tile = IMG_Load(tileset);
    if(tile == NULL)
    {
        perror("Error loading TileSet");
        exit(errno);
    }

     for(i=minx;i<maxx;i++){
        for(j=0;j<nbRow;j++){
            posTile.x = i*TILE_SIZE-m->xScroll;
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
 *Management of horizontal scrolling of the map
 *\param[in,out] map The map to scroll
 *\param[in] direction The direction of the scrolling
 */
void scrolling(Map *m, int direction){
    switch (direction){
        case RIGHT:
            if(m->xScroll < (m->lvl->width+1)*TILE_SIZE-m->screenWidth)
                m->xScroll+= TILE_SIZE;
            break;

        case LEFT:
            if(m->xScroll > TILE_SIZE)
                m->xScroll-= TILE_SIZE;
            break;
        default: ;
    }
}


/**
 *\fn  Map *initMap(Level *lvl,SDL_Surface *screen){
 *Initialize the map
 *\param[in] screen The screen of the game
 *\param[in] level The level of the map
 *\return a pointer on the map initialized
 */
 Map *initMap(Level *lvl,SDL_Surface *screen){
    Map *m;

    m = (Map *)malloc(sizeof(Map));
    if (m == NULL){
        perror("Error allocating memory");
        exit(errno);
    }
    m->lvl=lvl;
    m->screenHeight = screen->h;
    m->screenWidth = screen->w;
    m->xScroll = 20;

    return m;
 }

 /**
  *\fn void freeMap(map *m)
  *Free the memory allocated to the map
  *\param[in,out] m The map freed
  */

void freeMap(Map *m){
    closeLevel(m->lvl);
    free((void *)m);
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


    /*if ((level_name = (char *)malloc(MAX_LENGTH_FILE_NAME*sizeof(char))) == NULL){

            printf("\nError allocating memory\n");
            perror("");
            exit(1);
        }*/

    ptr_file_level = fopen("level/level", "r+");

    if(ptr_file_level == NULL){

        printf("Failed to open file /level/level\n");
        exit(1);
    }

    level_list = readLevelFile(&level_number);
    printf("%d\n", level_number);
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

    fclose(ptr_file_level);
    printf("Map %s saved\n", level_name_tmp);
    /*  Write the level in the file */

    sprintf(level_name,"level/%s.lvl",level_name_tmp);


    writeLevel(level_name, m->lvl);

    closeLevelList(level_list, (level_number));
    //free(level_name);
}


/**
  *\fn void reinitMap(map *m)
  *Fill a map with blank tiles. This function doesn't change the current map file.
  *\param[in,out] m The map to reinit
  */

/*void reinitMap(Map *m){

}*/

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
