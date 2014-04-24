/*!
 * \file const.h
 * \brief containe the program constantes
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

    #define TILE_SIZE            16 // Taille d'un bloc (carré) en pixels

    #define LARGEUR_FENETRE         960
    #define HAUTEUR_FENETRE         528
    #define FPS                     60
    #define MAX_SIZE_FILE_NAME      100
    #define MARGE_SCROLLING         2
    #define DEPLACEMENT_POURCENTAGE 0


    #define MAX_FALL_SPEED          10
    #define GRAVITY_SPEED           1
    #define JUMP_HEIGHT             13
    #define MAX_SPEED               5
    #define IMG_END_SIZE            80
    #define NB_TILE_MARYO_WIDTH     4
    #define NB_TILE_MARYO_HEIGHT    2



    #define TILE_MAX 8


    enum {VOID=0, GRASS1=1, GROUND1=2, GREY_WALL=3};
    enum {RIGHT,LEFT,UP,DOWN};

typedef struct{
    unsigned char**map;
    int width;
    int height;
    int timer_level;
    char tileSet[MAX_SIZE_FILE_NAME];
    char background[MAX_SIZE_FILE_NAME];
    char music[MAX_SIZE_FILE_NAME];
}Level;

typedef struct{
    Level *lvl;
    int xScroll;
    int screenWidth,screenHeight;
}Map;



#endif // CONST_H_INCLUDED

