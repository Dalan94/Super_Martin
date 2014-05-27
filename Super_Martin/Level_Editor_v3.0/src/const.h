/*!
 * \file const.h
 * \brief contient les constantes du programme
 * \author Xavier COPONET, Glenn HERROU
 * \date 2014-02-27
 */

#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

/*!
 * \def TILE_SIZE
 * The tile size
 */
#define TILE_SIZE               16

/*!
 * \def NB_TILES_X
 * The number of tile on x
 */
#define NB_TILES_X              80

/*!
 * \def NB_TILES_Y
 * The number of tile on y
 */
#define NB_TILES_Y              45

/*!
 * \def SCREEN_WIDTH
 * The screen width
 */
#define SCREEN_WIDTH            TILE_SIZE * NB_TILES_X

/*!
 * \def SCREEN_HEIGHT
 * The screen height
 */
#define SCREEN_HEIGHT           TILE_SIZE * NB_TILES_Y

/*!
 * \def TILESET_SIZE
 * The tilset size
 */
#define TILESET_SIZE            20

/*!
 * \def OPTIONS_PER_COLUMN
 * The number of options per column
 */
#define OPTIONS_PER_COLUMN      9

/*!
 * \def FPS
 * The FPS
 */
#define FPS                     60

/*!
 * \def SCROLLING_MARGIN
 * The scrolling margin
 */
#define SCROLLING_MARGIN        2

/*!
 * \def MAX_LENGTH_FILE_NAME
 * The size max of the filenames
 */
#define MAX_LENGTH_FILE_NAME    100

/**
 *\def min(a,b)
 * mix
 */
#define min(a,b) (a<=b?a:b)


enum {VOID=0, GROUND, COIN=7, ROCK, SPRING, HAMMER, HEART, ADDLIFE, ENEMY, CANON_R, CANON_L,CANON_B, TREE, FLOWER, CLOUD, PLATFORMV, PLATFORMH};

enum {RIGHT,LEFT,UP,DOWN};





#endif // CONST_H_INCLUDED

