/*!
 * \file player.c
 * \brief contient les fonction pour manipuler le joueur
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#include "player.h"

/**
 *\fn Character *createrCharacter(char *spR,char *spL)
 *créer un personnage
 *\param[in] spR l'adresse de la sprite droite
 *\param[in] spL l'adresse de la sprite gauche
 *\return le pointeur sur la structure créée
 */
Character *createrCharacter(char *spR,char *spL){
    Character *c;
    c = (Character *)malloc(sizeof(Character));
    if(c == NULL){
        perror("allocation error");
        exit(errno);
    }

    c->spriteR = IMG_Load(spR);
    c->spriteL = IMG_Load(spL);
    c->location.h = c->spriteR->h;
    c->location.w = c->spriteR->w;

    c->location.x = c->location.y = 0;

    return c;
}

/**
 *\fn void moveCharacter(Character *c,int direction)
 *déplace le personnage selon la direction
 *\param[in,out] c Le personnage
 *\param[in] direction La direction du déplacement
 */
void moveCharacter(Character *c,int direction){

}
