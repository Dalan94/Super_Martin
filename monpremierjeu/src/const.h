/*!
 * \file const.h
 * \brief contient les constantes du programme
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

    #define TAILLE_BLOC         20 // Taille d'un bloc (carré) en pixels
    #define NB_BLOCS_LARGEUR    48
    #define NB_BLOCS_HAUTEUR    27
    #define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
    #define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR
    #define FPS                 60


    enum {VOID=0, GRASS1=1, GROUND1=2, GREY_WALL=3};
    enum {JUMP,RIGHT,LEFT};

typedef struct{
    unsigned char **lvl;
    int nbBlocLg, nbBlocHt;
    int xScroll;
    int screenWidth,screenHeight;
}Map;

typedef struct{
    unsigned char**map;
    int width;
    int height;
}Level;

#endif // CONST_H_INCLUDED

