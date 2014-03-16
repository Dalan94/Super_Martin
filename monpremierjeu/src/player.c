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
 *\return 1 si le personnage a pu se deplacer, 0 sinon
 */
int moveCharacter(Character *c,int direction,Map *m,float speed){
    int vx = 0,vy = 0;
    movementVector(direction,&vx,&vy,speed);

    if(tryMovement(c,vx,vy,m))
        return 1;
    presiseMoveCharacter(c,vx,vy,m);
    return 0;
}

/**
 *\fn int tryMovement(Character *c,int vx,in vy,Map *m)
 *try to move a character
 *\param[in,out] c the character
 *\param[in] vx the horizontal component of the movement vector
 *\param[in] vy the vertical component of the movement vector
 *\param[in] m the map the character is on

 *\return 1 if the character could be moved, 0 if not
 */
int tryMovement(Character *c,int vx,int vy,Map *m){
    SDL_Rect futureLocation = c->location;
    futureLocation.x += vx;
    if(vx > 0){
        c->isRight =1;
    }else {
        c->isRight = 0;
    }
    futureLocation.y += vy;

    if(!collisionSprite(futureLocation,m)){
        c->location = futureLocation;
        return 1;
    }
    return 0;
}


/**
 *\fn void movementVector(int direction, int *vx, int *vy,int speed)
 *create a movement vector
 *\param[in] direction The movement's direction
 *\param[out] vx the horizontal component of the vector
 *\param[out] vy the vertical component of the vector
 *\param[in] speed the speed of the move
 */
void movementVector(int direction, int *vx, int *vy,int speed){
    switch(direction){
        case LEFT:
            *vx = 0-speed;
            break;
        case RIGHT:
            *vx = 0+ speed;
            break;
        case DOWN:
            *vy = 0+speed;
            break;
        case UP:
            *vy = 0-speed;
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
    test.h = test.w = TAILLE_BLOC;

    if(r.x+r.w > (m->lvl->width+1)*TAILLE_BLOC || r.x < TAILLE_BLOC)
        return 1; //test les limites du monde

    xmin =  (r.x) / TAILLE_BLOC -1;
    xmax =  (r.x + r.w )  / TAILLE_BLOC ;
    ymin = (r.y) / TAILLE_BLOC ;
    ymax =  (r.y + r.h ) / TAILLE_BLOC +1;

    for(i = xmin ; i< xmax ; i++){
        for (j=ymin ; j< ymax ; j++){
            if(m->lvl->map[j][i] != VOID){
                test.x = i*TAILLE_BLOC;
                test.y = j*TAILLE_BLOC;
                if(!(((r.x+r.w < test.x)
                    && (r.x > test.x+test.w))
                    && ((r.y+r.h <= test.y)
                    && (r.y >= test.y+test.h)))
                )
                    return 1;
            }
        }
    }

    return 0;
}

/**
 *\fn void gravity(Character *c,Map *m)
 *apply gravity to a Character
 *\param[in,out] c the Character
 *\param[in] m The map the Character is on
 */
void gravity(Character *c, Map *m){
    /*GravityApplication *g;
    g =(GravityApplication *)malloc(sizeof(GravityApplication));
    SDL_TimerID timer ;

    g->c = c;
    g->direction = DOWN;
    g->m = m;
    g->speed = 4;

    timer = SDL_AddTimer(17,falling,g);*/


    moveCharacter(c,DOWN,m,4);


}

/**
 *\fn Uint32 falling(Uint32 interval, void *param)
 *make the Character falling while in void
 *\param[in] interval the duration between two calls of this function
 *\param[in,out] param the structure containing the parameters of moveCharacter
 \return interval
 */
Uint32 falling(Uint32 interval, void *param){
    GravityApplication *gra = param;
    moveCharacter(gra->c,gra->direction,gra->m,gra->speed);
    return interval;
}

/**
 *\fn void presiseMoveCharacter(Charactere *c, int vx,int vy, Map m*)
 *make a more presise move of a character if he can still move but the distance between it and the obstacle is less than its speed
 *\param[in,out] c the charactere
 *\param[in] m the map
 *\param[in] vx the horizontal component of the movement vector
 *\param[in] vy the vertical component of the movement vector
 */
void presiseMoveCharacter(Character *c, int vx,int vy, Map *m){
    int i,j;

    for(i = 0 ; i < ABS(vx) ; i++){

            if(!tryMovement(c,SGN(vx),0,m))
                break;
    }
    for(j = 0 ; j < ABS(vy) ; j++){
        if(!tryMovement(c,0,SGN(vy),m))
                break;
    }
}


