/*!
 * \file const.h
 * \brief contient les constantes du programme
 * \author Xavier COPONET, Glenn HERROU
 * \date 2014-02-27
 */

#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

    #define TILE_SIZE               16
    #define NB_TILES_X              60
    #define NB_TILES_Y              33
    #define SCREEN_WIDTH            TILE_SIZE * NB_TILES_X
    #define SCREEN_HEIGHT           TILE_SIZE * NB_TILES_Y
    #define TILESET_LAST            8

    #define FPS                     60
    #define SCROLLING_MARGIN        2
    #define MAX_LENGTH_FILE_NAME    100

    #define TRANS_R                 255
    #define TRANS_G                 255
    #define TRANS_B                 255


    enum {VOID=0, GRASS1=1, GROUND1=2, GREY_WALL=3};
    enum {RIGHT,LEFT,UP,DOWN};





#endif // CONST_H_INCLUDED
