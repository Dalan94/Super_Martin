/*!
 * \file const.h
 * \brief contient les constantes du programme
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

    #define TAILLE_BLOC             16 // Taille d'un bloc (carré) en pixels
    #define NB_BLOCS_LARGEUR        60
    #define NB_BLOCS_HAUTEUR        33
    #define LARGEUR_FENETRE         TAILLE_BLOC * NB_BLOCS_LARGEUR
    #define HAUTEUR_FENETRE         TAILLE_BLOC * NB_BLOCS_HAUTEUR
    #define FPS                     60
    #define TAILLE_MAX_NOM_FICHIER    100
    #define MARGE_SCROLLING         2
    #define POURCENTAGE_DEPLACEMENT 0


    #define MAX_FALL_SPEED          10
    #define GRAVITY_SPEED           1
    #define JUMP_HEIGHT             13
    #define MAX_SPEED               5
    #define IMG_END_SIZE            80


    #define TILE_MAX 8


    enum {VOID=0, GRASS1=1, GROUND1=2, GREY_WALL=3};
    enum {RIGHT,LEFT,UP,DOWN};

typedef struct{
    unsigned char**map;
    int width;
    int height;
    int timer_level;
    char tileSet[TAILLE_MAX_NOM_FICHIER];
    char background[TAILLE_MAX_NOM_FICHIER];
    char music[TAILLE_MAX_NOM_FICHIER];
}Level;

typedef struct{
    Level *lvl;
    int xScroll;
    int screenWidth,screenHeight;
}Map;



#endif // CONST_H_INCLUDED

