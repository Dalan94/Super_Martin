#include "defs.h"


/* Structures utilisees pour gérer le jeu */

/* Structure utilisee pour gérer l'input */



typedef struct Input {

    int left, right, up, down, add, remove;
    int previous, next, load, save,copy, reinit;
    int mouseX, mouseY;

}Input;


typedef struct Cursor {

    int x, y, tileID;
}Cursor;

/* Structure utilisee pour gérer le niveau */

typedef struct Gestion {

    SDL_Surface *screen;

}Gestion;


/*  Structure utilisee pour gerer la map */

typedef struct Map {

    SDL_Surface *background, *tileSet;

/*  Coordonnees de debut */

    int startX, startY;

/*  Coordonnees max de fin */

    int maxX, maxY;

/*  Tableau representant la map */

    int tile[MAX_MAP_Y][MAX_MAP_X];

}Map;
