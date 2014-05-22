/*!
 * \file character.c
 * \brief manipulate character
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#include "character.h"



Character *createCharacter(char *tile,int x, int y,int npc, int nbProjectile, int nbCoins, int nbLifes)
{
    Character *c;
    c = (Character *)malloc(sizeof(Character));
    if(c == NULL){
        perror("allocation error");
        exit(errno);
    }
    c->isNpc = npc;

    if(tile != NULL)
    {
        c->tile = imageLoadAlpha(tile);
        c->location.h = c->tile->h/NB_TILE_MARYO_HEIGHT;
        c->location.w = c->tile->w/NB_TILE_MARYO_WIDTH;
    }
    else
        c->tile = NULL;

//    c->location.h = c->tile->h/NB_TILE_MARYO_HEIGHT;
//    c->location.w = c->tile->w/NB_TILE_MARYO_WIDTH;
    c->saveY=c->location.y = y;
    c->saveX = c->location.x = x;

    c->dirX = c->dirY = 0;

    c->isRight = 1;
    c->isOnGround = 0;
    c->doubleJump = 0;
    c->wallJump = 0;

    c->countStars = nbCoins;
    c->nbLifes = nbLifes;
    c->hp = 100;
    c->nbProjectile = nbProjectile;
    c->isHurt = 0;
    c->isFalling = 0;
    c->moving=0;
    c->OnPlatform = -1;

    return c;
}


int moveCharacter(Character *c,float move_left, float move_right,int jump,Map *m,float* speed,list *l,Sound *sound_sys,platformSet *ps)
{
    c->dirX = 0;
    int ret;
    float s;
    if(move_left < 2 && move_right < 2)
        s = *speed;
    else
    {
        if(move_right < 2)
            s = move_left;
        if(move_left < 2)
            s = move_right;
    }
    *speed = s;

    if(c->location.y == c->saveY)
    {
        c->dirY = 0;
        c->isFalling = 0;
    }
    c->saveY = c->location.y;

    if(jump == 2 && c->doubleJump != 2)
        c->dirY = -GRAVITY_SPEED*3;


    c->dirY+=GRAVITY_SPEED;

    if(c->dirY >= MAX_FALL_SPEED)
        c->dirY = MAX_FALL_SPEED;


        /*left*/
    if (move_right && !move_left)
    {
        c->dirX += s;
        if(l != NULL)
            c->isRight = 1;
    }
        /* right*/
    if (move_left && !move_right)
    {
        c->dirX -= s;
        if(l != NULL)
            c->isRight = 0;
    }

    /* jump */
    if(jump==1 && (c->isOnGround || c->doubleJump == 1))
    {
        c->dirY = -JUMP_HEIGHT;
        if(c->isOnGround)
        {
            playShortSound("sound/jump_big.ogg",sound_sys);
            c->isOnGround = 0;
        }
        else
            c->doubleJump = 2;
    }
    if(c->wallJump == 4)
    {
        c->dirX = -5;
        c->isRight = 0;
        if(checkWall(c,m) == 1)
            c->wallJump = 0;
    }
    if(c->wallJump == 5)
    {
        c->dirX = 5;
        c->isRight = 1;
        if(checkWall(c,m) == 2)
            c->wallJump = 0;
    }
    if(jump == 3)
    {
        c->dirY = -JUMP_HEIGHT;
        c->wallJump = 4;
        c->isOnGround = 0;
    }
    if(jump == 4)
    {
        c->dirY = -JUMP_HEIGHT;
        c->wallJump = 5;
        c->isOnGround = 0;
    }


    c->isFalling=1;

    ret = tryMovement(c,c->dirX,c->dirY,m,l,ps,sound_sys);
    if(ret == 1)
        return 1;
    if(ret == 0)
        presiseMoveCharacter(c,c->dirX,c->dirY,m,l,ps);

    if(checkWall(c,m)&&c->dirX > 0 && c->wallJump <= 3 && checkFall(c,m,ps))
        c->wallJump = 1;
    if(checkWall(c,m)&&c->dirX < 0 && c->wallJump <= 3 && checkFall(c,m,ps))
        c->wallJump = 2;

    if(!checkFall(c,m,ps))
    {
        c->isOnGround = 1;
        c->isFalling = 0;
        c->doubleJump = 0;
        c->wallJump = 0;
    }
     if(c->location.y == c->saveY /*&& !c->wallJump*/)
    {
        c->isFalling = 0;
        c->isOnGround = 1;
        c->doubleJump = 0;
    }

    return 0;
}

int tryMovement(Character *c,int vx,int vy,Map *m,list *l,platformSet *ps,Sound *sound_sys)
{
    int ret = 0;
    int coins = c->countStars/100;
    SDL_Rect futureLocation = c->location;
    futureLocation.x += vx;

    futureLocation.y += vy;
    if(!c->isNpc)
    {
        if(c->isRight)
            futureLocation.x += COLLISION_ADJUSTMENT;

        futureLocation.w -= COLLISION_ADJUSTMENT;
    }

    ret = collisionMap(futureLocation,m);
    if((ret != 1) && !collisionEnemy(c,l,m) && (collisionPlatform(c,ps,futureLocation)!=1))
    {
        if(!c->isNpc)
        {
            if(c->isRight)
                futureLocation.x -= COLLISION_ADJUSTMENT;
            futureLocation.w += COLLISION_ADJUSTMENT;
        }

        switch (ret)
        {
            case 2:
                c->countStars++;
                coins++;
                if((c->countStars) > 100)
                {
                    c->nbLifes++;
                    //coins = 0;
                    c->countStars = 0;
                }
                break;
            case 3:
                if(!c->isNpc)
                {
                    c->dirY = -SPRING_HEIGHT;
                    c->isOnGround = 0;
                    c->doubleJump = 2;
                    playShortSound("sound/spring.wav",sound_sys);
                }
                else
                    futureLocation.y -= vy;
                break;
            case 4:
                c->nbProjectile++;

            case 5 :
                c->hp += 50;
                break;
            case 6 :

                break;
            default:;
        }
        c->location = futureLocation;
        return 1;
    }
    return 0;
}

int collisionSprite(SDL_Rect s1, SDL_Rect s2)
{

    if((s1.x+s1.w < s2.x)
            || (s1.x > s2.x+s2.w)
            || (s1.y+s1.h < s2.y)
            || (s1.y > s2.y+s2.h)
     )
        return 0;
    if(s1.y+s1.h<s2.y+10)
    {
        return 2;
    }
    if(s2.y+s2.h<s1.y+10)
        return 3;
    return 1;
}


void blitCharacter(SDL_Surface *screen, Character *c,Map *m)
{
    SDL_Rect pos,poseTile;

    pos.y = c->location.y;
    pos.x = c->location.x - m->xScroll;
    pos.h = poseTile.h = c->tile->h/NB_TILE_MARYO_HEIGHT;
    pos.w = poseTile.w = c->tile->w/NB_TILE_MARYO_WIDTH;

    switch(c->isRight)
    {
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
            if (c->moving< FPS/(FRENQUENCY_CHANGE_MOVING  *2))
            {
                poseTile.x = poseTile.w;
                c->moving++;
            }
            else
            {
                poseTile.x = poseTile.w *2;
                if (c->moving == FPS/FRENQUENCY_CHANGE_MOVING  )
                    c->moving=0;
                else
                    c->moving ++;
            }
        }
    }

    SDL_BlitSurface(c->tile,&poseTile,screen,&pos);
}

void presiseMoveCharacter(Character *c, int vx,int vy, Map *m,list *l,platformSet *ps)
{
    int i,j;

    for(i = 0 ; i < ABS(vx) ; i++)
    {

            if(!tryMovement(c,SGN(vx),0,m,l,ps,NULL))
                break;
    }
    for(j = 0 ; j < ABS(vy) ; j++)
    {
        if(!tryMovement(c,0,SGN(vy),m,l,ps,NULL))
                break;
    }
}

int checkWall(Character *c,Map *m)
{
    int x,y;

    if(!c->isRight)
    {

        x = (int)((c->location.x-2)/TILE_SIZE);
        y = (int)(c->location.y + TILE_SIZE)/TILE_SIZE;


        if(y<0)
            y = 1;
        if(y >= m->lvl->height-1)
            y = m->lvl->height-2;
        if(x<0)
            x = 1;
        if(x> m->lvl->width)
            x = m->lvl->width;

        if(m->lvl->map[y][x-1] != VOID && m->lvl->map[y][x] < 65)
            return 1;
        else
            return 0;
    }
    else
    {
        x = (int)(c->location.x)/TILE_SIZE;
        y = (int)(c->location.y + TILE_SIZE)/TILE_SIZE;


        if(y<=0)
            y = 1;
        if(y >= m->lvl->height-1)
            y = m->lvl->height - 2;
        if(x<=0)
            x = 1;
        if(x>= m->lvl->width)
            x = m->lvl->width - 1;

        if(m->lvl->map[y][x+1] != VOID && m->lvl->map[y][x+1]<65)
            return 2;
        else
            return 0;
    }
    return 0;
}

int checkFall(Character *c,Map *m,platformSet *ps)
{
    int x,y;
    int i;

    if(!c->isRight)
    {
        if(ps != NULL)
            for(i = 0;i<ps->nb;i++)
                if(c->location.y+c->location.h<=ps->tab[i]->location.y+50
                    && c->location.y+c->location.h>=ps->tab[i]->location.y-50
                    && c->location.x>=ps->tab[i]->location.x
                    && c->location.x<=ps->tab[i]->location.x+ps->tab[i]->location.w)
                        return 0;
        if(c->isNpc)
        {
            x = (int)(c->location.x + c->dirX)/TILE_SIZE;
            y = (int)(c->location.y + c->location.h - 1)/TILE_SIZE;
        }
        else
        {
            x = (int)((c->location.x+c->location.w/2)/TILE_SIZE);
            y = (int)(c->location.y + c->location.h - 1)/TILE_SIZE;
        }

        if(y<0)
            y = 1;
        if(y >= m->lvl->height-1)
            y = m->lvl->height-2;
        if(x<0)
            x = 1;
        if(x> m->lvl->width)
            x = m->lvl->width;

        if(m->lvl->map[y+1][x] == VOID)
            return 1;
        else
            return 0;
    }
    else
    {
        if(ps != NULL)
            for(i = 0;i<ps->nb;i++)
                if(c->location.y+c->location.h<=ps->tab[i]->location.y+50
                    && c->location.y+c->location.h>=ps->tab[i]->location.y-50
                    && c->location.x+c->location.w>=ps->tab[i]->location.x
                    && c->location.x+c->location.w<=ps->tab[i]->location.x+ps->tab[i]->location.w)
                        return 0;
        if(c->isNpc)
        {
            x = (int)(c->location.x + c->dirX + c->location.w)/TILE_SIZE;
            y = (int)(c->location.y + c->location.h - 1)/TILE_SIZE;
        }
        else
        {
            x = (int)(c->location.x/*+c->location.w/2*/)/TILE_SIZE;
            y = (int)(c->location.y + c->location.h - 1)/TILE_SIZE;
        }

        if(y<=0)
            y = 1;
        if(y >= m->lvl->height-1)
            y = m->lvl->height - 2;
        if(x<=0)
            x = 1;
        if(x>= m->lvl->width)
            x = m->lvl->width - 1;

        if(m->lvl->map[y+1][x] == VOID)
            return 1;
        else
            return 0;
    }
    return 0;
}
