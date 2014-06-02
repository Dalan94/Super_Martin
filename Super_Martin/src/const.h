/*!
 * \file const.h
 * \brief containe the program constantes
 * \author Xavier COPONET
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
 * \def SCREEN_WIDTH
 * The screen width
 */
#define SCREEN_WIDTH            1280

/*!
 * \def SCREEN_HEIGHT
 * The screen height
 */
#define SCREEN_HEIGHT           720

/*!
 * \def FPS
 * The FPS
 */
#define FPS                     60

/*!
 * \def MAX_SIZE_FILE_NAME
 * The size max of the filenames
 */
#define MAX_SIZE_FILE_NAME      100

/*!
 * \def MARGE_SCROLLING
 * The marge of scrolling
 */
#define MARGE_SCROLLING         2

/*!
 * \def DEPLACEMENT_POURCENTAGE
 * The deplacement pourcentage of scrooling
 */
#define DEPLACEMENT_POURCENTAGE 0

/*!
 * \def GRAVITY_SPEED
 * The gravity speed
 */
#define GRAVITY_SPEED           1

/*!
 * \def JUMP_HEIGHT
 * The jump height
 */
#define JUMP_HEIGHT             13

/*!
 * \def MAX_SPEED
 * The max speed
 */
#define MAX_SPEED               5

/*!
 * \def SPRING_HEIGHT
 * The spring height
 */
#define SPRING_HEIGHT           22

/*!
 * \def COLLISION_ADJUSTMENT
 * Collision adjustement
 */
#define COLLISION_ADJUSTMENT 9

/*!
 * \def IMG_END_SIZE
 * The image size end
 */
#define IMG_END_SIZE            80

/*!
 * \def NB_TILE_MARYO_WIDTH
 * The number of tile width of maryo
 */
#define NB_TILE_MARYO_WIDTH     4

/*!
 * \def NB_TILE_MARYO_HEIGHT
 * The number of tile height of maryo
 */
#define NB_TILE_MARYO_HEIGHT    2

/*!
 * \def TILE_MAX
 * The the tile max
 */
#define TILE_MAX                18

/*!
 * \def FRENQUENCY_CHANGE_MOVING
 * The frequency of changing the legs of maryo when moving
 */
#define FRENQUENCY_CHANGE_MOVING        5

/*!
 * \def MAX_NB_PLATFORM
 * The the number max of platform
 */
#define MAX_NB_PLATFORM         30

/*!
 * \def PLATFORM_SPEED
 * The platform speed
 */
#define PLATFORM_SPEED          1

/*!
 * \def MAX_NB_PROJECTILE
 * The number max of projectile
 */
#define MAX_NB_PROJECTILE      30

/*!
 * \def PROJECTILE_SPEED
 * The projectile speed
 */
#define PROJECTILE_SPEED        10

/*!
 * \def FRENQUENCY_ROCKET_LAUNCH
 * The frequency of rocket launch
 */
#define FRENQUENCY_ROCKET_LAUNCH 2000

/*!
 * \def NB_KEY
 * The number of key
 */
#define NB_KEY                  6

enum {VOID=0, GROUND, COIN=7, ROCK, SPRING, HAMMER, HEART, ADDLIFE, ENEMY, TREE, FLOWER, CLOUD,CANON_L=17,CANON_R,CANON_B};

/**
 *\def min(a,b)
 * mix
 */
#define min(a,b) (a<=b?a:b)

enum {RIGHT,LEFT,UP,DOWN};

enum {L=0,R,J,P,H};





#endif // CONST_H_INCLUDED

