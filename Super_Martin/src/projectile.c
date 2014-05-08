/**
 *\file projectile.c
 *\brief containes the functions to deal with the projectiles
 *\author X.COPONET
 *\date 2014-05-08
*/

#include "projectile.h"

/**
 *\fn void initProjSet(projectileSet *projSet)
 *initialize a projectile set
 *\param[out] projSet the projectile set to be initialized
 */
void initProjSet(projectileSet *projSet)
{
    int i;
    for(i = 0; i<NB_PROJECTILE_MAX;i++)
        projSet->tab[i] = NULL;

    projSet->nb = 0;
    projSet->projectileThrown = 0;
}

/**
 *\fn void freeProjectileSet(projectileSet *ps)
 *free all the projectiles
 *\param[int,out] ps the projectile set
 */
void freeProjectileSet(projectileSet *ps)
{
    int i;
    for(i = 0;i<ps->nb;i++)
        free((void *)ps->tab[i]);
}

/**
 *\fn void createProjectile(projectileSet *projSet, int dir, int x, int y)
 *creates a projectile and adds it to the projectile set
 *\param[in,out] projSet the projectile set
 *\param[in] dir the projectile's direction
 *\param[in] x the start absciss coordinate of the projectile
 *\param[in] y the start ordinate coordinate of the projectile
*/
void createProjectile(projectileSet *projSet, int dir, int x, int y)
{
    projectile* p;

    if(projSet->nb >= NB_PROJECTILE_MAX)
        return ; //si trop de projectiles, il ne se passe rien

    p = (projectile *)malloc(sizeof(projectile));
    if(p == NULL)
    {
        perror("allocation error");
        exit(errno);
    }
    if(dir == RIGHT)
        p->sprite = imageLoadAlpha("sprites/hammerR.png");
    else
        p->sprite = imageLoadAlpha("sprites/hammerL.png");

    if(p->sprite == NULL)
    {
        perror("error while loading projectile sprite");
        exit(errno);
    }

    p->direction = dir;
    p->location.x = x;
    p->location.y = y;
    p->location.w = p->sprite->w;
    p->location.h = p->sprite->h;

    projSet->tab[projSet->nb] = p;
    projSet->nb++;
}

/**
 *\fn void deleteProjectile(projectileSet *ps,int nb)
 *delete a projectile
 *\param[out] ps the projectile Set
 *\param[in] nb the number of the projectile which has to be deleted
 */
void deleteProjectile(projectileSet *ps,int nb)
{
    int i;
    free((void *) ps->tab[nb]);

    for(i = nb; i<NB_PROJECTILE_MAX;i++)
    {
        ps->tab[i] = ps->tab[i+1];
    }
    ps->nb--;
}

/**
 *\fn void blitProjectile(SDL_Surface *screen, projectileSet *ps, Map *m)
 *blit the projectiles on the game screen
 *\param[in,out] screen game screen
 *\param[in,out] projSet the projectile set
 *\param[in] m the current level map
 */
void blitProjectile(SDL_Surface *screen, projectileSet *ps, Map *m)
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
 *\fn void moveProjectiles(Map *m,projectileSet *ps,list *l)
 *moves all the projectiles
 *\param[in,out] m the game map
 *\param[in,out] ps the projectile set
 *\param[in,out] l the enemy list
 */
void moveProjectiles(Map *m,projectileSet *ps,list *l)
{
    int i;

    for (i = 0 ; i<ps->nb;i++)
    {
        moveOneProjectile(m,ps,l,i);
    }
}


/**
 *\fn void moveOneProjectile(Map *m,projectileSet *ps,list *l,int nb)
 *moves one projectile
 *\param[in,out] m the game map
 *\param[in,out] ps the projectileSet
 *\param[in,out] l the enemy list
 *\param[in] the number of the projectile which is moved
 */
void moveOneProjectile(Map *m,projectileSet *ps,list *l,int nb)
{
    projectile *p = ps->tab[nb];
    if(p->direction == RIGHT)
    {
        p->location.x += PROJECTILE_SPEED;
    }
    else
        p->location.x -= PROJECTILE_SPEED;

    if(collisionMap(p->location,m) == 1)
        /*if the pojectile is in collision with the map, it is deleted */
        deleteProjectile(ps,nb);

    if(p->location.x < m->xScroll || p->location.x > m->xScroll+m->screenWidth)
        /*if the projectile gets out of the screen, it is deleted*/
        deleteProjectile(ps,nb);

    /* projectile collision with enemies */
    setOnFirst(l);
    while(!outOfList(l))
    {
        if(collisionSprite(p->location,l->current->c->location))
        {
            deleteCurrent(l);
            deleteProjectile(ps,nb);
            break;
        }
        next(l);
    }
}
