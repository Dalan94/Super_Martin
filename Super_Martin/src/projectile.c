/**
 *\file projectile.c
 *\brief contains the functions to deal with the projectiles
 *\author X.COPONET
 *\date 2014-05-08
*/

#include "projectile.h"


void initProjSet(projectileSet *projSet)
{
    int i;
    for(i = 0; i<NB_PROJECTILE_MAX;i++)
        projSet->tab[i] = NULL;

    projSet->nb = 0;
    projSet->projectileThrown = 0;
}


void freeProjectileSet(projectileSet *ps)
{
    int i;
    for(i = 0;i<ps->nb;i++)
        free((void *)ps->tab[i]);
}


void createProjectile(projectileSet *projSet,char *pathSprite,int dir, int x, int y, int fromNPC)
{
    projectile* p;
    char path[MAX_SIZE_FILE_NAME];

    if(projSet->nb >= NB_PROJECTILE_MAX)
        return ; //si trop de projectiles, il ne se passe rien

    p = (projectile *)malloc(sizeof(projectile));
    if(p == NULL)
    {
        perror("allocation error");
        exit(errno);
    }
    if(dir == RIGHT)
    {
        sprintf(path,"sprites/%sR.png",pathSprite);
        p->sprite = imageLoadAlpha(path);
    }
    else
    {
        sprintf(path,"sprites/%sL.png",pathSprite);
        p->sprite = imageLoadAlpha(path);
    }

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

    p->fromNPC = fromNPC;

    projSet->tab[projSet->nb] = p;
    projSet->nb++;
}


void deleteProjectile(projectileSet *ps,int nb)
{
    int i;
    free((void *) ps->tab[nb]);

    for(i = nb; i<ps->nb;i++)
    {
        ps->tab[i] = ps->tab[i+1];
    }
    ps->tab[NB_PROJECTILE_MAX-1] = NULL;

    ps->nb--;
}


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


void moveProjectiles(Character *c,Map *m,projectileSet *ps,list *enemyList)
{
    int i;

    for (i = 0 ; i<ps->nb;i++)
    {
        moveOneProjectile(c,m,ps,enemyList,i);
    }
}



void moveOneProjectile(Character *c,Map *m,projectileSet *ps,list *l,int nb)
{
    projectile *p = ps->tab[nb];
    if(p->direction == RIGHT)
    {
        p->location.x += PROJECTILE_SPEED;
    }
    else
        p->location.x -= PROJECTILE_SPEED;

    if(p->location.x < m->xScroll || p->location.x > m->xScroll+m->screenWidth)
        /*if the projectile gets out of the screen, it is deleted*/
        deleteProjectile(ps,nb);

    /* projectile collision with enemies */
    if(!p->fromNPC)
    {
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
    else
    {
        if(collisionSprite(c->location,p->location) == 2)
        {
            c->dirY = -JUMP_HEIGHT;
            deleteProjectile(ps,nb);
        }
        else if(collisionSprite(c->location,p->location) != 0)
        {
            c->hp -= 50;
            deleteProjectile(ps,nb);
        }
    }

    if(collisionMap(p->location,m) == 1)
        /*if the pojectile is in collision with the map, it is deleted */
        deleteProjectile(ps,nb);
}
