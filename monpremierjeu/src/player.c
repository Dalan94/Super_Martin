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
    c->isRight = 1;

    return c;
}

/**
 *\fn void moveCharacter(Character *c,int direction, Map *m)
 *déplace le personnage selon la direction
 *\param[in,out] c Le personnage
 *\param[in] direction La direction du déplacement
 *\param[in] m la carte sur laquelle le personnage se déplace
 */
void moveCharacter(Character *c,int direction,Map *m){
    switch (direction){
        case RIGHT:
            if(c->location.x+c->spriteL->w < m->nbBlocLg*TAILLE_BLOC)
                (c->location.x)++;
            c->isRight = 1;
            break;
        case LEFT:
            if(c->location.x > TAILLE_BLOC)
                (c->location.x)--;
            c->isRight = 0;
            break;
        default: ;
    }
}

/**
 *\fn void blitCharacter(SDL_Surface *screen, Character *c, Map *m)
 *blit le personnage à l'écran
 *\param[in,out] screen L'écran
 *\param[in] c Le personnage
 *\param[in] m la carte du jeu
 */
void blitCharacter(SDL_Surface *screen, Character *c,Map *m){
    SDL_Rect pos;
    pos.y = c->location.y;
    pos.x = c->location.x - m->xScroll;
    switch(c->isRight){
        case 0:
            SDL_BlitSurface(c->spriteL,NULL,screen,&pos);
            break;
        case 1:
            SDL_BlitSurface(c->spriteR,NULL,screen,&pos);
            break;
        default:;
    }
}
