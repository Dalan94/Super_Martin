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
 *\fn void moveCharacter(Character *c,int direction, Map *m,float speed)
 *déplace le personnage selon la direction
 *\param[in,out] c Le personnage
 *\param[in] direction La direction du déplacement
 *\param[in] m la carte sur laquelle le personnage se déplace
 *\param[in] speed la vitesse de déplacement
 */
void moveCharacter(Character *c,int direction,Map *m,float speed){
    SDL_Rect futureLocation = c->location;
    switch (direction){
        case RIGHT:
            (futureLocation.x)+=speed;
            c->isRight = 1;
            break;
        case LEFT:
            (futureLocation.x)-=speed;
            c->isRight = 0;
            break;
        default: ;
    }

    if(!collisionSprite(futureLocation,m)){
        c->location = futureLocation;
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

/**
 *\fn int collisionSprite(SDL_Rect r,Map *m)
 *détermine s'il y a collision entre une sprite et le décor
 *\param[in] r le SDL_Rect correspondant à la sprite
 *\param[in] m la carte contenant le décor
 *\return 1 s'il y a collision ou si en dehors du monde, 0 sinon
 */
int collisionSprite(SDL_Rect r,Map *m){
    int i,j;
    int xmin,xmax,ymin,ymax;
    SDL_Rect test;

    if(r.x+r.w > m->nbBlocLg*TAILLE_BLOC || r.x < TAILLE_BLOC)
        return 1; //test les limites du monde

    xmin =  (r.x) / TAILLE_BLOC ;
    xmax =  (r.x + r.w )  / TAILLE_BLOC ;
    ymin = (r.y) / TAILLE_BLOC ;
    ymax =  (r.y + r.h ) / TAILLE_BLOC ;

    for(i = xmin ; i< xmax ; i++){
        for (j=ymin ; j< ymax ; j++){
            if(m->lvl[i][j] != VOID){
                test.x = i*TAILLE_BLOC;
                test.y = j*TAILLE_BLOC;
                if((r.x+r.w <= test.x)
                    || (r.x >= test.x+test.w)
                    || (r.y+r.h <= test.y)
                    || (r.y >= test.y+test.h)
                )
                    return 1;
            }
        }
    }

    return 0;
}

