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
    memset(ps->tab,0,NB_PLATFORM_MAX*sizeof(platform));
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
    p->location.y = (y1+y2)/2;
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
}
