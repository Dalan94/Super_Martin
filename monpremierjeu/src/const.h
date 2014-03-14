/*!
 * \file const.h
 * \brief contient les constantes du programme
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

    #define TAILLE_BLOC         20 // Taille d'un bloc (carré) en pixels
    #define NB_BLOCS_LARGEUR    32
    #define NB_BLOCS_HAUTEUR    24
    #define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
    #define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR


    enum {VOID=0, GRASS1, GROUND1, PEACH};
    enum {JUMP,RIGHT,LEFT};

#endif // CONST_H_INCLUDED

