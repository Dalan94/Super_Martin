/**
 *\file mobile_platform.c
 *\brief containe the functions to deal with the mobile platforms
 *\author X.COPONET
 *\date 2014-05-01
*/

#include "mobile_platform.h"

/**
 *\fn void initPlatformSet(platformSet *ps)
 *initialize a platform set
 *\param[in] ps the platform set to be initialized
 */
void initPlatformSet(platformSet *ps)
{
    int i;
    for(i = 0; i<NB_PLATFORM_MAX;i++)
        ps->tab[i] = NULL;

    ps->nb = 0;
}

/**
 *\fn void createPlatform(platformSet *ps,int x1,int y1,int x2, int y2)
 *creates of new platform and adds it to the platform set
 *\param[in,out] ps the platform set
 *\param[in] x1 the x low limit for deplacement
 *\param[in] x2 the x high limit for deplacement
 *\param[in] y1 the y low limit for deplacement
 *\param[in] y2 the y high limit for deplacement
 */
void createPlatform(platformSet *ps,int x1,int y1,int x2, int y2)
{
    platform *p;
    if(ps->nb >= NB_PLATFORM_MAX)
    {
        fprintf(stderr,"too many platform");
        exit(EXIT_FAILURE);
    }

    p = (platform *)malloc(sizeof(platform));
    if(p == NULL)
    {
        perror("platform allocation error");
        exit(errno);
    }

    p->sprite = imageLoadAlpha("sprites/moving_platform.png");
    if(p->sprite == NULL)
    {
        perror("error while loading platform sprite");
        exit(errno);
    }
    p->location.x = (x1+x2)/2;
    p->location.y = (y1);
    p->location.w = p->sprite->w;
    p->location.h = p->sprite->h;

    p->xMax = x2;
    p->xMin = x1;
    p->yMax = y2;
    p->yMin = y1;
    if(x1 == x2)
    {
        p->type = 1;
        p->direction = DOWN;
    }
    if(y1 == y2)
    {
        p->type = 0;
        p->direction = RIGHT;
    }


    ps->tab[ps->nb] = p;
    ps->nb++;
}

/**
 *\fn void blitPlatform(SDL_Surface *screen, platformSet *ps, Map *m)
 *blit the platforms on the game screen
 *\param[in,out] screen game screen
 *\param[in,out] ps the platform set
 *\param[in] m the current level map
 */
void blitPlatform(SDL_Surface *screen, platformSet *ps, Map *m)
{
    int i;
    SDL_Rect pos;

    for (i = 0 ; i < ps->nb ; i++)
    {
        pos = ps->tab[i]->location;
        pos.x -= m->xScroll;

        SDL_BlitSurface(ps->tab[i]->sprite,NULL,screen,&pos);
    }
}

/**
 *\fn void movePlatform(Character *c,platformSet *ps,list *l)
 *moves all the platforms
 *\param[in,out] c the player
 *\param[in,out] ps the platform set
 *\param[in,out] l the enemy list
 */
void movePlatform(Character *c,platformSet *ps,list *l)
{
    int i;

    for (i = 0 ; i<ps->nb;i++)
    {
        moveOnePlatform(c,ps->tab[i],l,i);
    }
}

/**
 *\fn void moveOnePlatform(Character *c,platform *,list *l,int nb)
 *moves one platforms
 *\param[in,out] c the player
 *\param[in,out] p the platform
 *\param[in,out] l the enemy list
 *\param[in] the number of the platform which is moved
 */
void moveOnePlatform(Character *c,platform *p,list *l,int nb)
{
    if(!p->type)
    {
        if(p->location.x <= p->xMin)
            p->direction = RIGHT;
        if(p->location.x >=p->xMax)
            p->direction = LEFT;

        if(p->direction == RIGHT)
        {
            p->location.x += PLATFORM_SPEED;
            if(c->OnPlatform == nb)
                c->location.x += PLATFORM_SPEED;
        }
        if(p->direction == LEFT)
        {
            p->location.x -= PLATFORM_SPEED;
            if(c->OnPlatform == nb)
                c->location.x -= PLATFORM_SPEED;
        }

        if(c->OnPlatform == nb)
            c->location.y = p->location.y - c->location.h-1;
    }
    else
    {
        if(p->location.y <= p->yMin)
            p->direction = DOWN;
        if(p->location.y >=p->yMax)
            p->direction = UP;

        if(p->direction == DOWN)
        {
            /*if(c->OnPlatform)
                c->location.y += PLATFORM_SPEED;*/
            p->location.y += PLATFORM_SPEED;
        }
        if(p->direction == UP)
        {
            /*if(c->OnPlatform)
                c->location.y -= PLATFORM_SPEED;*/
            p->location.y -= PLATFORM_SPEED;
        }
        if(c->OnPlatform == nb)
            c->location.y = p->location.y - c->location.h-1;
    }
}

/**
 *\fn int collisionPlatform(Character *c,platformSet *ps)
 *determine if there is a collision beteewen the player and a mobile platform and deals with
 *\param[in,out] c the player
 *\param[in,out] ps the platform set
 *\param[in] futurLocation the tryMovement variabla to test the future position
 *\return 1 if there is a collision, 0 if not
 */
int collisionPlatform(Character *c,platformSet *ps,SDL_Rect futureLocation)
{
    int i,ret;

    if(ps == NULL || ps->nb == 0)
        return 0;

    for(i = 0; i<ps->nb;i++)
    {
        ret = collisionSprite(futureLocation,ps->tab[i]->location);
        if(ret)
        {
            if(ret == 2)
            {
                c->OnPlatform = i;
                /*c->isOnGround = 1;
                c->isFalling = 0;
                c->doubleJump = 0;*/
                c->dirY = 0;
            }
            return 1;
        }
        c->OnPlatform = -1;
    }

    return 0;
}

/**
 *\fn void freePlatformSet(platformSet *ps)
 *free all the platforms
 *\param[int,out] ps the platform set
 */
void freePlatformSet(platformSet *ps)
{
    int i;
    for(i = 0;i<ps->nb;i++)
        free((void *)ps->tab[i]);
}

