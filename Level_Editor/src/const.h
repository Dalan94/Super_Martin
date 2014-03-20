/*!
 * \file const.h
 * \brief Definitions of every constants and structures used
 * \author Xavier COPONET, Glenn HERROU
 * \date 2014-03-18
 */

#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


#define TILE_SIZE               16
#define NB_TILES_X              60
#define NB_TILES_Y              34
#define SCREEN_WIDTH            TILE_SIZE * NB_TILES_X
#define SCREEN_HEIGHT           TILE_SIZE * NB_TILES_Y
#define TILESET_LAST            8

#define FPS                     60

#define MAX_LENGTH_FILE_NAME    100

#define TRANS_R                 255
#define TRANS_G                 255
#define TRANS_B                 255



    enum {RIGHT,LEFT,UP,DOWN};

typedef struct Level{

    unsigned char**map;
    int width;
    int height;
    int timer_level;
    char music[MAX_LENGTH_FILE_NAME];
    char background[MAX_LENGTH_FILE_NAME];

}Level;

typedef struct Map{

    Level *lvl;
    int xScroll;
    int screenWidth,screenHeight;
}Map;

typedef struct Cursor{

    int x;
    int y;
    int tileID;
}Cursor;

typedef struct Input{

    int left;
    int right;
    int add;
    int remove;
    int previous;
    int next;
    int load;
    int save;
    int copy;
    int reinit;
    int mouseX;
    int mouseY;
}Input;


#endif // CONST_H_INCLUDED

