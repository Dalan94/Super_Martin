#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>

/*  Taille de la fenetre */

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

/*  Valeurs RGB pour la transparence */


#define TRANS_R 255
#define TRANS_G 255
#define TRANS_B 255

/*  Taille maxi de la map en tiles */

#define MAX_MAP_X 400
#define MAX_MAP_Y 34

/*  Taille d'une tile en pixels */

#define TILE_SIZE 16

/*  N° de la tile transparente */

#define BLANK_TILE 0

/*  N° de la derniere tile */

#define MAX_TILES 8

#define GAMEOVER_TIME 50
