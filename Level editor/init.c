#include "init.h"


/*  Fonction initialisant le Jeu */


void init(char *title){



    /*  Initialisation la SDL
    *   Si la valeur retournee est 0, erreur d'initialisation => arret du programme
    */

    if(SDL_Init(SDL_INIT_VIDEO) < 0){

        printf("Could not Initialize SDL : %s\n", SDL_GetError());
        exit(1);
    }

    /*  Creation de la fenetre */

    jeu.screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_HWPALETTE | SDL_DOUBLEBUF);

    /*  Arret du programme si la creation a echouee */

    if(jeu.screen == NULL){

        printf("Couldn't set screen mode to %d x %d : %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    /*  Definition du titre de la fenetre */

    SDL_WM_SetCaption(title, NULL);
}

/*  Fonction chargeant les ressources */

void loadGame(void){

    /*  Chargement de l'image de fond */

    map.background = loadImage("sprites/Background/green_hills_3.png");

    map.tileSet = loadImage("sprites/Tuto/Tiles/tilesetok.png");

    loadMap("sprites/Tuto/Map/map4.txt");
}

/* Fonction quittant le jeu */

void cleanup(){


    /*  Liberation de l'espace alloue a l'image de fond */

    if(map.background != NULL){

        SDL_FreeSurface(map.background);
    }

    /*  Liberation de l'espace alloue a l'image du tileset */

    if(map.tileSet != NULL){

        SDL_FreeSurface(map.tileSet);
    }

    /*  Quitte la SDL */

    SDL_Quit();

}
