/*!
 * \file character.c
 * \brief manipulate character
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#include "character.h"


/**
 *\fn Character *createrCharacter(char *spR,char *spL,int x,int y)
 *create a character
 *\param[in] spR right sprite address
 *\param[in] spL right sprite address
 *\param[in] x character's x location
 *\param[in] y character's y location
 *\return character structure pointer
 */
Character *createrCharacter(char *spR,char *spL,int x, int y, int x1,int x2)
{
    Character *c;
    c = (Character *)malloc(sizeof(Character));
    if(c == NULL){
        perror("allocation error");
        exit(errno);
    }

    c->spriteR = imageLoadAlpha(spR);
    c->spriteL = imageLoadAlpha(spL);
    c->location.h = c->spriteR->h;
    c->location.w = c->spriteR->w;

    c->location.x = x;
    c->location.y = y;
    c->isRight = 1;
    c->isOnGround = 0;
    c->isJumping = 0;
    c->life = 100;
    c->isHurt = 0;
    c->isFalling = 0;

    c->x1 = x1;
    c->x2 = x2;

    return c;
}

/**
 *\fn void moveCharacter(Character *c,int direction, Map *m,float speed)
 *move player according to the direction
 *\param[in,out] c the character
 *\param[in] direction movement direction
 *\param[in] m level map
 *\param[in] speed movement speed
 *\return 1 if character was moved without using the precise movement function, 0 if not
 */
int moveCharacter(Character *c,int direction,Map *m,float speed,list *l)
{
    int vx = 0,vy = 0;
    movementVector(direction,&vx,&vy,speed,c);
    if(vy>0)
        c->isFalling = 1;

    if(tryMovement(c,vx,vy,m,l))
        return 1;
    presiseMoveCharacter(c,vx,vy,m,l);
    if(vy>0)
    {
        c->isOnGround = 1;
        c->isFalling = 0;
    }
    return 0;
}

/**
 *\fn int tryMovement(Character *c,int vx,in vy,Map *m)
 *try to move a character
 *\param[in,out] c the character
 *\param[in] vx the horizontal component of the movement vector
 *\param[in] vy the vertical component of the movement vector
 *\param[in] m the map the character is on
 *\return 1 if the character can be moved, 0 if not
 */
int tryMovement(Character *c,int vx,int vy,Map *m,list *l)
{
    SDL_Rect futureLocation = c->location;
    futureLocation.x += vx;

    futureLocation.y += vy;

    if(!collisionMap(futureLocation,m) && !collisionEnemy(c,l))
    {
        c->location = futureLocation;
        return 1;
    }
    return 0;
}


/**
 *\fn void movementVector(int direction, int *vx, int *vy,int speed,Character *c)
 *create a movement vector
 *\param[in] direction The movement's direction
 *\param[out] vx the horizontal component of the vector
 *\param[out] vy the vertical component of the vector
 *\param[in] speed the speed of the move
 *\param[out] c the Character you have to move
 */
void movementVector(int direction, int *vx, int *vy,int speed,Character *c){
    switch(direction){
        case LEFT:
            *vx = 0-speed;
            c->isRight = 0;
            break;
        case RIGHT:
            *vx = 0+ speed;
            c->isRight = 1;
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
 *blit the character
 *\param[in,out] screen game screen
 *\param[in] c the character
 *\param[in] m game map
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
 *\fn int collisionMap(SDL_Rect r,Map *m)
 *determine if there is a collision beteewen a sprite and a "wall" of the map
 *\param[in] r SDL_Rect corresponding to the sprite
 *\param[in] m map
 *\return 1 if there is a collision, 0 if not
 */
int collisionMap(SDL_Rect r,Map *m){
    int i,j;
    int xmin,xmax,ymin,ymax;
    SDL_Rect test;
    test.h = test.w = TAILLE_BLOC;

    if(r.x+r.w > (m->lvl->width+1)*TAILLE_BLOC || r.x < TAILLE_BLOC || r.y+r.h >(m->lvl->height)*TAILLE_BLOC -1 || r.y<0)
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
 *int collisionSprite(SDL_Rect s1, SDL_Rect s2)
 *determine if there is a collision beteewen two sprites
 *\param[in] s1 the first sprite
 *\param[in] s2 the second sprite
 *\return 1 if there is a collision and s1 is below s2, 2 if there is a collision and s1 is over s2, 0 if there is no collision
*/
int collisionSprite(SDL_Rect s1, SDL_Rect s2)
{
    if((s1.x+s1.w < s2.x)
            || (s1.x > s2.x+s2.w)
            || (s1.y+s1.h <= s2.y)
            || (s1.y >= s2.y+s2.h)
     )return 0;
    if(s1.y+s1.h<=s2.y+10)
    {
        return 2;
    }
    return 1;
}

/**
 *\fn void gravity(Character *c,Map *m)
 *apply gravity to a Character
 *\param[in,out] c the Character
 *\param[in] m The map the Character is on
 */
void gravity(Character *c, Map *m,list *l)
{

        if (moveCharacter(c,DOWN,m,10,l) != 0)
            c->isOnGround = 0;
}


/**
 *\fn void presiseMoveCharacter(Charactere *c, int vx,int vy, Map m*)
 *make a more presise move of a character if he can still move but the distance between it and the obstacle is less than its speed
 *\param[in,out] c the charactere
 *\param[in] m the map
 *\param[in] vx the horizontal component of the movement vector
 *\param[in] vy the vertical component of the movement vector
 */
void presiseMoveCharacter(Character *c, int vx,int vy, Map *m,list *l){
    int i,j;

    for(i = 0 ; i < ABS(vx) ; i++){

            if(!tryMovement(c,SGN(vx),0,m,l))
                break;
    }
    for(j = 0 ; j < ABS(vy) ; j++){
        if(!tryMovement(c,0,SGN(vy),m,l))
                break;
    }
}

/**
 *\fn void jumping(Character *c, Map *m)
 *make the character jump
 *\param[in,out] c the Character
 *\param[in] m The map the Character is on
 */
void jumping(Character *c, Map *m,Sound *jump_sound,list *l)
{
    if(c->isOnGround)
    {
        playMusicOnce(jump_sound,"sound/jump_big.ogg");
    }

    c->isOnGround = 0;
    if (c->isJumping < 6)
        moveCharacter(c,UP,m,c->isJumping,l);
    else
        moveCharacter(c,UP,m,6,l);
    c->isJumping --;

}
