#include "map.h"

void loadMap(char *name){
    int x, y;
    FILE *fp;
    int maxX, maxY;

    fp = fopen(name, "r");

    /* Si on ne peut pas ouvrir le fichier, on quitte */

    if (fp == NULL)
    {
        printf("Failed to open map %s\n", name);

        exit(1);
    }

    /* Lit les données du fichier dans la map */
    fseek(fp, 0, SEEK_SET);
    fscanf(fp, "%d", &maxX);
    fscanf(fp, "%d", &maxY);
    fseek(fp, -((maxX+1)*maxY), SEEK_END);
    map.maxX = map.maxY = 0;

    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            /* On lit le numéro de la tile et on le copie dans notre tableau */


            map.tile[y][x] = fgetc(fp);

            if(map.tile[y][x] == '\n'){

                map.tile[y][x] = fgetc(fp);
            }

            map.tile[y][x] -= '0';


            /* Permet de déterminer la taille de la map (voir plus bas) */
            if (map.tile[y][x] > 0)
            {
                if (x > map.maxX)
                {
                    map.maxX = x;
                }

                if (y > map.maxY)
                {
                    map.maxY = y;
                }
            }
        }
    }
}


void saveMap(char *name_lst){

    int x, y;
    int lvl_number = 0;
    char name_dest[100] = "level/Map_";
    FILE *fp, *fplst;

    fplst = fopen(name_lst, "r+");

    if(fplst == NULL){

        printf("Failed to open file %s\n", name_lst);
        exit(1);
    }


    lvl_number = fgetc(fplst);
    name_dest[10] = lvl_number;
    name_dest[11] = '\0';
    lvl_number -= '0';
    fseek(fplst, 0, SEEK_SET);
    fprintf(fplst, "%d\n", lvl_number+1);
    fseek(fplst, 0, SEEK_END);
    fprintf(fplst, "Map_%d\n", lvl_number);

    //fprintf(fplst, "Map_%d\n", lvl_number);
    fclose(fplst);
    strncat(name_dest, ".lvl", 5);

    fp = fopen(name_dest, "w+");

    if(fp == NULL){

        printf("Failed to open map %s\n", name_dest);
        exit(1);
    }

    fprintf(fp, "%d\n%d\n%d\nsprites/Background/green_hills_3.png\nsound/ezer_ev.mp3\n", map.maxX/TILE_SIZE, map.maxY/TILE_SIZE, GAMEOVER_TIME);

    /*  Sauvegarde de la map */

    for(y = 0; y < MAX_MAP_Y; y++){

        for(x = 0; x < MAX_MAP_X; x++){

            fprintf(fp, "%d", map.tile[y][x]);
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
}


void reinitMap(char *name){

    int x, y, maxX, maxY;
    FILE *fp;

    fp = fopen(name, "w+");

    if(fp == NULL){

        printf("Failed to open map %s\n", name);
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);
    fscanf(fp, "%d", &maxX);
    fscanf(fp, "%d", &maxY);
    fseek(fp, -((maxX+1)*maxY), SEEK_END);
    fprintf(fp, "%d\n%d\nsprites/Background/green_hills_3.png\nsound/ezer_ev.mp3\n", map.maxX/TILE_SIZE, map.maxY/TILE_SIZE);

    /*  Remplissage de la map avec des 0 */

    for(y = 0; y < MAX_MAP_Y; y++){

        for(x = 0; x < MAX_MAP_X; x++){

            fprintf(fp, "0 ");
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
}


void drawMap(char *tileset){

    SDL_Surface *tile;
    SDL_Rect posTile, posTileSet;
    int i,j;
    int minx, maxx, nbRow;
    int xsrc, ysrc;

    posTile.h = posTile.w = posTileSet.h = posTileSet.w = TILE_SIZE;

    minx = map.startX/TILE_SIZE-1;
    maxx = (map.startX + MAX_MAP_X*TILE_SIZE)/TILE_SIZE+1;
    nbRow = MAX_MAP_Y;

    tile = IMG_Load(tileset);
    if(tile == NULL)
    {
        perror("error while loading TileSet");
        exit(1);
    }

     for(i=minx;i<maxx;i++){
        for(j=0;j<nbRow;j++){
            posTile.x = (i+1)*TILE_SIZE-map.startX;
            posTile.y = j*TILE_SIZE;
            posTileSet.x = map.tile[j][i] % 8 * TILE_SIZE;
            posTileSet.y = map.tile[j][i] / 8 * TILE_SIZE;

            if(i>=0 && i<MAX_MAP_X)
            {
                SDL_BlitSurface(tile,&posTileSet,jeu.screen,&posTile);
            }
        }
    }

    SDL_FreeSurface(tile);


    /*  Affichage de la tile selctionnee a cote du curseur */

    ysrc = cursor.tileID / MAX_TILES * TILE_SIZE;
    xsrc = cursor.tileID % MAX_TILES * TILE_SIZE;
    drawTile(map.tileSet, cursor.x, cursor.y, xsrc, ysrc);

}
