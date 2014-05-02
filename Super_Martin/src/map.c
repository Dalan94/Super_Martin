/*!
 * \file map.c
 * \brief loading and displaying the map
 * \author Xavier COPONET
 * \date 2014-03-18
 */

#include "map.h"

/**
 *\fn void updateScreenMap(SDL_Surface *screen, Map *m,char *tileset)
 *update and display the map
 *\param[in,out] screen of the game
 *\param[in] Map *m The map
 */
void updateScreenMap(SDL_Surface *screen, Map *m)
{
    SDL_Surface *tile;
    SDL_Surface *end = NULL;
    SDL_Surface *spring;
    SDL_Rect posTile, posTileSet;
    int i,j,minx,maxx,nbRow;

    posTile.h = posTile.w = posTileSet.h = posTileSet.w = TILE_SIZE;

    minx = m->xScroll/TILE_SIZE-1;
    maxx = (m->xScroll + m->screenWidth)/TILE_SIZE+1;
    nbRow = m->screenHeight/TILE_SIZE;
    //if(m->lvl->tileSetUse)
        tile = imageLoadAlpha(m->lvl->tileSet);
   // else
        spring = imageLoadAlpha("sprites/spring1.png");

     for(i=minx;i<maxx;i++)
     {
        for(j=0;j<nbRow;j++)
        {
            posTile.x = (i+1)*TILE_SIZE-m->xScroll;
            posTile.y = j*TILE_SIZE;
            posTileSet.x = m->lvl->map[j][i] % TILE_MAX * TILE_SIZE;
            posTileSet.y = m->lvl->map[j][i] / TILE_MAX * TILE_SIZE;

            if(i>=0 && i<m->lvl->width)
            {
                if(m->lvl->map[j][i] != SPRING)
                    SDL_BlitSurface(tile,&posTileSet,screen,&posTile);
                else
                    if(!m->lvl->tileSetUse)
                        SDL_BlitSurface(spring,NULL,screen,&posTile);
                    else
                        SDL_BlitSurface(tile,&posTileSet,screen,&posTile);
            }
        }
    }

    if (maxx >= m->lvl->width - IMG_END_SIZE / TILE_SIZE + 1)
    {
        end = imageLoadAlpha("sprites/ending.png");

        posTile.x = (m->lvl->width - IMG_END_SIZE / TILE_SIZE + 2)*TILE_SIZE - m->xScroll - IMG_END_SIZE/2;
        i=0;
        while (m->lvl->map[i][m->lvl->width- IMG_END_SIZE / TILE_SIZE + 1] == 0)
            i++;

        if (i*TILE_SIZE - IMG_END_SIZE > 0)
            posTile.y=i*TILE_SIZE - IMG_END_SIZE;
        else
            posTile.y=0;

        SDL_SetAlpha(end, SDL_SRCALPHA, 200);
        SDL_BlitSurface(end,NULL,screen,&posTile);

        SDL_FreeSurface(end);
    }

    SDL_FreeSurface(tile);

}

/**
 *\fn void scrolling(Map *m,int direction,float speed)
 *scroll the map
 *\param[in,out] map the lvl
 *\param[in] direction scrolling direction
 *\param[in] speed scrolling speed
 */
void scrolling(Map *m, int direction,float speed){
    switch (direction){
        case RIGHT:
            if(m->xScroll < (m->lvl->width+1)*TILE_SIZE-m->screenWidth)
                m->xScroll+= speed;
            break;

        case LEFT:
            if(m->xScroll > TILE_SIZE)
                m->xScroll-= speed;
            break;
        default: ;
    }
}

/**
 *\fn  Map *initMap(SDL_Surface *screen,char * level_name,list *l)
 *initialize the map
 *\param[in] screen game screen
 *\param[in] level_name lvl name
 *\return pointer on the map
 */
 Map *initMap(SDL_Surface *screen,char * level_name,list *l)
 {
    Map *m;

    m = (Map *)malloc(sizeof(Map));
    if (m == NULL){
        perror("allocation error");
        exit(errno);
    }
    m->lvl=openLevel(level_name,l);
    m->screenHeight = screen->h;
    m->screenWidth = screen->w;
    m->xScroll = 20;

    return m;
 }

 /**
  *\fn void freeMap(map *m)
  *free memory allocated to the map
  *\param[in,out] m the map
  */
void freeMap(Map *m){
    closeLevel(m->lvl);
    free((void *)m);
}

/**
 *\fn int collisionMap(SDL_Rect r,Map *m)
 *determine if there is a collision beteewen a sprite and a "wall" of the map
 *\param[in] r SDL_Rect corresponding to the sprite
 *\param[in] m map
 *\return 1 if there is a collision, 0 if not,2 if collision with star/coin, 3 if spring
 */
int collisionMap(SDL_Rect r,Map *m)
{
    int i,j;
    int xmin,xmax,ymin,ymax;
    SDL_Rect test;
    test.h = TILE_SIZE;
    test.w = 2*TILE_SIZE;
    if(r.y < 0)
        return 0;
    if(r.x+r.w > (m->lvl->width+1)*TILE_SIZE || r.x < TILE_SIZE || r.y+r.h >(m->lvl->height)*TILE_SIZE -1)
        return 1; //test les limites du monde

    xmin =  (r.x) / TILE_SIZE -1;
    xmax =  (r.x + r.w )  / TILE_SIZE ;
    ymin = (r.y) / TILE_SIZE ;
    ymax =  (r.y + r.h ) / TILE_SIZE +1;

    for(i = xmin ; i< xmax ; i++)
    {
        for (j=ymin ; j< ymax ; j++)
        {
            if(m->lvl->map[j][i] != VOID)
            {
                test.x = i*TILE_SIZE;
                test.y = j*TILE_SIZE;
                test.h = TILE_SIZE;
                if(collisionSprite(r,test))
                    switch(m->lvl->map[j][i])
                    {
                        case COIN:
                            m->lvl->map[j][i] = VOID;
                            return 2;
                            break;
                        case SPRING:
                            return 3;
                            break;
                        default:
                            return 1;
                    }
            }
        }
    }

    return 0;
}
