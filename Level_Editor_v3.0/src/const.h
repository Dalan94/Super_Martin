/*!
 * \file const.h
 * \brief contient les constantes du programme
 * \author Xavier COPONET, Glenn HERROU
 * \date 2014-02-27
 */

#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

    #define TILE_SIZE               16
    #define NB_TILES_X              80
    #define NB_TILES_Y              45
    #define SCREEN_WIDTH            TILE_SIZE * NB_TILES_X
    #define SCREEN_HEIGHT           TILE_SIZE * NB_TILES_Y
    #define TILESET_SIZE            16
    #define OPTIONS_PER_COLUMN      8
    #define FPS                     60
    #define SCROLLING_MARGIN        2
    #define MAX_LENGTH_FILE_NAME    100

    #define TRANS_R                 255
    #define TRANS_G                 255
    #define TRANS_B                 255

    #define min(a,b) (a<=b?a:b)

    enum {VOID=0, GROUND, COIN=7, ROCK, SPRING, ENEMY, TREE, FLOWER, CLOUD, PLATFORMV, PLATFORMH};
    enum {RIGHT,LEFT,UP,DOWN};





#endif // CONST_H_INCLUDED

