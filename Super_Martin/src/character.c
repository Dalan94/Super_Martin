/*!
 * \file character.c
 * \brief manipulate character
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#include "character.h"


/**
 *\fn Character *createrCharacter(char *spR,char *spL,int x,int y,int npc)
 *create a character
 *\param[in] spR right sprite address
 *\param[in] spL right sprite address
 *\param[in] x character's x location
 *\param[in] y character's y location
 *\param[in] npc 1 if creating a npc, 0 if not
 *\return character structure pointer
 */
Character *createrCharacter(char *tile,int x, int y,int npc)
{
    Character *c;
    c = (Character *)malloc(sizeof(Character));
    if(c == NULL){
        perror("allocation error");
        exit(errno);
    }
    c->isNpc = npc;

    c->tile = imageLoadAlpha(tile);

    c->location.h = c->tile->h/NB_TILE_MARYO_HEIGHT;
    c->location.w = c->tile->w/NB_TILE_MARYO_WIDTH;
    c->saveY=c->location.y = y;
    c->saveX = c->location.x = x;

    c->dirX = c->dirY = 0;

    c->isRight = 1;
    c->isOnGround = 0;
    c->isJumping = 0;
    c->life = 100;
    c->countStars = 5;
    c->isHurt = 0;
    c->isFalling = 0;

    return c;
}

/**
 *\fn int moveCharacter(Character *c,int move_left, int move_right,int jump,Map *m,float speed,list *l)
 *move player according to the direction
 *\param[in,out] c the character
 *\param[in] move_left indicates if must go to the left
 *\param[in] move_right indicates if must go to the right
 *\param[in] jump indicates if must jump
 *\param[in] m level map
 *\param[in] speed movement speed
 *\param[in,out] l the enemy list
 *\param[out] sound_sys the sound system
 *\return 1 if character was moved without using the precise movement function, 0 if not
 */


int moveCharacter(Character *c,int move_left, int move_right,int jump,Map *m,float speed,list *l,Sound *sound_sys)
{
    c->dirX = 0;

    if(c->location.y == c->saveY)
        c->dirY = 0;
    c->saveY = c->location.y;

    if(jump == 2)
        c->dirY = -GRAVITY_SPEED*3;

    c->dirY+=GRAVITY_SPEED;
    if(c->dirY >= MAX_FALL_SPEED)
        c->dirY == MAX_FALL_SPEED;

    if(jump==1 && c->isOnGround)
    {
        c->dirY = -JUMP_HEIGHT;
        c->isOnGround = 0;
        playShortSound("sound/jump_big.ogg",sound_sys);
    }

    if (move_right && !move_left)
    {
        c->dirX += speed;
        c->isRight = 1;
    }
    if (move_left && !move_right)
    {
        c->dirX -= speed;
        c->isRight = 0;
    }

    if (c->dirY > 0)
        c->isFalling=1;

    if(tryMovement(c,c->dirX,c->dirY,m,l))
        return 1;
    presiseMoveCharacter(c,c->dirX,c->dirY,m,l);

    if(c->dirY>0)
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
    int ret = 0;
    SDL_Rect futureLocation = c->location;
    futureLocation.x += vx;

    futureLocation.y += vy;

    ret = collisionMap(futureLocation,m);
    if((!ret || ret == 2) && !collisionEnemy(c,l,m))
    {
        c->location = futureLocation;
        if(ret == 2)
            c->countStars++;
        return 1;
    }
    return 0;
}


/**
 *\fn void blitCharacter(SDL_Surface *screen, Character *c, Map *m)
 *blit the character
 *\param[in,out] screen game screen
 *\param[in] c the character
 *\param[in] m game map
 */
void blitCharacter(SDL_Surface *screen, Character *c,Map *m){
    SDL_Rect pos,poseTile;
    static char deplacement=1;

    pos.y = c->location.y;
    pos.x = c->location.x - m->xScroll;
    pos.h = poseTile.h = c->tile->h/NB_TILE_MARYO_HEIGHT;
    pos.w = poseTile.w = c->tile->w/NB_TILE_MARYO_WIDTH;

    switch(c->isRight){
        case 0:
            poseTile.y = 0;
            break;
        case 1:
            poseTile.y = poseTile.h;
            break;
        default:;
    }

    if (c->isFalling)
        poseTile.x=3*poseTile.w;
    else
    {
        if(c->dirX == 0)
            poseTile.x=0;

        else
        {
            if (deplacement < FPS)
            {
                poseTile.x = poseTile.w;
                deplacement++;
            }
            else
            {
                poseTile.x = poseTile.w *2;
                if (deplacement == 2*FPS)
                    deplacement=0;
                else
                    deplacement ++;
            }
        }
    }

    SDL_BlitSurface(c->tile,&poseTile,screen,&pos);
}

/**
 *\fn int collisionMap(SDL_Rect r,Map *m)
 *determine if there is a collision beteewen a sprite and a "wall" of the map
 *\param[in] r SDL_Rect corresponding to the sprite
 *\param[in] m map
 *\return 1 if there is a collision, 0 if not,2 if collision with star/coin
 */
int collisionMap(SDL_Rect r,Map *m){
    int i,j;
    int xmin,xmax,ymin,ymax;
    SDL_Rect test;
    test.h = TILE_SIZE;
    test.w = 2*TILE_SIZE;
    if(r.x+r.w > (m->lvl->width+1)*TILE_SIZE || r.x < TILE_SIZE || r.y+r.h >(m->lvl->height)*TILE_SIZE -1 || r.y<0)
        return 1; //test les limites du monde

    xmin =  (r.x) / TILE_SIZE -1;
    xmax =  (r.x + r.w )  / TILE_SIZE ;
    ymin = (r.y) / TILE_SIZE ;
    ymax =  (r.y + r.h ) / TILE_SIZE +1;

    for(i = xmin ; i< xmax ; i++){
        for (j=ymin ; j< ymax ; j++){
            if(m->lvl->map[j][i] != VOID)
            {
                test.x = i*TILE_SIZE;
                test.y = j*TILE_SIZE;
                if(collisionSprite(r,test))
                    if(m->lvl->map[j][i] != COIN)
                        return 1;
                    else
                    {
                        m->lvl->map[j][i] = VOID;
                        return 2;
                    }
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
            || (s1.y+s1.h < s2.y)
            || (s1.y > s2.y+s2.h)
     )return 0;
    if(s1.y+s1.h<=s2.y+10 || s2.y+s2.h<=s1.y+10)
    {
        return 2;
    }
    return 1;
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


