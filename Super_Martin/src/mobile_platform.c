/**
 *\file mobile_platform.c
 *\brief contains the functions to deal with the mobile platforms
 *\author X.COPONET
 *\date 2014-05-01
*/

#include "mobile_platform.h"


void initPlatformSet(platformSet *ps)
{
    int i;
    for(i = 0; i<NB_PLATFORM_MAX;i++)
        ps->tab[i] = NULL;

    ps->nb = 0;
}


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
        p->speed = (y2-y1)/100;
    }
    if(y1 == y2)
    {
        p->type = 0;
        p->direction = RIGHT;
        p->speed = (x2-x1)/100;
    }


    ps->tab[ps->nb] = p;
    ps->nb++;
}


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


void movePlatform(Character *c,platformSet *ps,list *l,Map *m)
{
    int i;

    for (i = 0 ; i<ps->nb;i++)
    {
        moveOnePlatform(c,ps->tab[i],l,i,m);
    }
}


void moveOnePlatform(Character *c,platform *p,list *l,int nb,Map *m)
{
    SDL_Rect futur;
    futur = p->location;

    if(!p->type)
    {
        if(p->location.x <= p->xMin)
            p->direction = RIGHT;
        if(p->location.x >=p->xMax)
            p->direction = LEFT;

        if(p->direction == RIGHT)
        {
            p->location.x += p->speed;
            if(c->OnPlatform == nb)
                c->location.x += p->speed; //déplacement si perso sur platform
            else if(collisionSprite(futur,c->location)==1)
            {
                c->location.x += p->speed; //déplacement si perso devant plateforme
                 if(checkWall(c,m))
                    c->hp = 0;
            }
        }
        if(p->direction == LEFT)
        {
            p->location.x -= p->speed;
            if(c->OnPlatform == nb)
                c->location.x -= p->speed;
            else if(collisionSprite(futur,c->location)==1)
            {
                c->location.x -= p->speed; //déplacement si perso devant plateforme
                if(checkWall(c,m))
                    c->hp = 0;
            }
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
            p->location.y += p->speed;
            if(collisionSprite(futur,c->location)==1)
            {
                c->location.y = p->location.y+p->location.h; //déplacement si perso sous plateforme
                if(!checkFall(c,m,NULL)) //if character stuck between a platform and the ground, kill him
                    c->hp = 0;
            }
        }
        if(p->direction == UP)
        {
            p->location.y -= p->speed;
        }
        if(c->OnPlatform == nb)
            c->location.y = p->location.y - c->location.h-1;
    }
}


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

/* ************************************** */
/* Gestion des .lvl pour les plateformes  */
/* ************************************** */


void platformMap(platformSet *ps, SDL_Rect array[],SDL_Rect mark,int vert)
{
    int i;
    for (i=0;i<NB_PLATFORM_MAX;i++)
    {
        if((vert && array[i].x == mark.x) || (!vert && array[i].y == mark.y)) //borne correspondante trouvée
        {
            createPlatform(ps,array[i].x,array[i].y,mark.x,mark.y);
            array[i].x = array[i].y = -1;
            return ;
        }
    }
    for ( i = 0;i<NB_PLATFORM_MAX;i++) //pas de borne correspondante trouvée
    {
        if(array[i].x==-1 && array[i].y == -1)// rien à cet emplacement
        {
            array[i] = mark;
            return ;
        }
    }
}


