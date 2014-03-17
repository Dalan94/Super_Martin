#include "map.h"


void loadMap(char *name){

    int x,y;
    FILE *fp;

    fp = fopen(name, "r");

    if(fp == NULL){

        printf("Failed to open map %s\n", name);
        exit(1);
    }

    /* Lecture des donnees du fichier map */

    map.maxX = map.maxY = 0;

    for(y = 0; y < MAX_MAP_Y; y++){

        for(x = 0; x < MAX_MAP_X; x++){

            /*  Lecture du numero de la tile et stockage dans le tableau */

            fscanf(fp, "%d", &map.tile[y][x]);

            /*  Determination de la taille de la map */

            if(map.tile[y][x] > 0){

                if(x > map.maxX){

                    map.maxX = x;
                }

                if(y > map.maxY){

                    map.maxY = y;
                }
            }
        }
    }

    map.maxX = MAX_MAP_X * TILE_SIZE;
    map.maxY = MAX_MAP_Y * TILE_SIZE;

    /*  Remise a zero des coordonnees de depart de la map */

    map.startX = map.startY = 0;

    /*  Fermeture du fichier */

    fclose(fp);
}


void saveMap(char *name){

    int x, y;
    FILE *fp;

    fp = fopen(name, "w+");

    if(fp == NULL){

        printf("Failed to open map %s\n", name);
        exit(1);
    }


    fprintf(fp, "%d\n%d\nsprites/Background/green_hills_3.png\nsound/ezer_ev.mp3\n", MAX_MAP_X, MAX_MAP_Y);

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

    int x, y;
    FILE *fp;

    fp = fopen(name, "w+");

    if(fp == NULL){

        printf("Failed to open map %s\n", name);
        exit(1);
    }

    fprintf("%d\n%d\n50\nsprites/Background/green_hills_3.png\nsound/ezer_ev.mp3", map.maxX, map.maxY);

    /*  Remplissage de la map avec des 0 */

    for(y = 0; y < MAX_MAP_Y; y++){

        for(x = 0; x < MAX_MAP_X; x++){

            fprintf(fp, "0 ");
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
}


void drawMap(void){

    int x,y, mapX, x1, x2, mapY, y1, y2, xsrc, ysrc, a;

    /*  Calcul de l'affichage de l'ecran pour le scrolling */

    /*  Initialisation de mapX a la 1ere colonne */

    mapX = map.startX / TILE_SIZE;

    /*  Coordonnee x de depart pour l'affichage de la map */

    x1 = (map.startX % TILE_SIZE) * (-1);

    /*  Coordonnee x de fin d'affichage de la map */

    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    /*  Initialisation de mapY a la 1ere ligne */

    mapY = map.startY / TILE_SIZE;

    /*  Coordonnee y de depart pour l'affichage de la map */

    y1 = (map.startY % TILE_SIZE) * (-1);

    /*  Coordonnee y de fin d'affichage de la map */

    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);



    /*  Dessin de la carte en commençant par startX et startY */

    for(y = y1; y < y2; y += TILE_SIZE){

        /* Reinitialisation de la colonne a chaque debut de ligne */

        mapX = map.startX / TILE_SIZE;

        /* Dessin de la tile suivant la colonne courante */

        for(x = x1; x < x2; x += TILE_SIZE){

        /*  Decoupage du tileset suivant le numero de notre tile */

        a = map.tile[mapY][mapX];

        /* Calcul des coordonnees du tile a traiter pour un tileset de 10 tiles par ligne */

        ysrc = a / MAX_TILES * TILE_SIZE;
        xsrc = a % MAX_TILES * TILE_SIZE;

        /* Blittage de la bonne tile au bon endroit */

        drawTile(map.tileSet, x, y, xsrc, ysrc);
        mapX++;
        }

    mapY++;
    }


    /*  Affichage de la tile selctionnee a cote du curseur */

    ysrc = cursor.tileID / MAX_TILES * TILE_SIZE;
    xsrc = cursor.tileID % MAX_TILES * TILE_SIZE;
    drawTile(map.tileSet, cursor.x, cursor.y, xsrc, ysrc);
}
