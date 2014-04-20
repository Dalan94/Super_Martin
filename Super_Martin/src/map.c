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
 *\param[in] tileset lvl tileset
 */
void updateScreenMap(SDL_Surface *screen, Map *m, char *tileset){
    SDL_Surface *tile;
    SDL_Surface *end = NULL;
    SDL_Rect posTile, posTileSet;
    int i,j,minx,maxx,nbRow;

    posTile.h = posTile.w = posTileSet.h = posTileSet.w = TAILLE_BLOC;

    minx = m->xScroll/TAILLE_BLOC-1;
    maxx = (m->xScroll + m->screenWidth)/TAILLE_BLOC+1;
    nbRow = m->screenHeight/TAILLE_BLOC;
    tile = imageLoadAlpha(tileset);

     for(i=minx;i<maxx;i++){
        for(j=0;j<nbRow;j++){
            posTile.x = (i+1)*TAILLE_BLOC-m->xScroll;
            posTile.y = j*TAILLE_BLOC;
            posTileSet.x = m->lvl->map[j][i] % TILE_MAX * TAILLE_BLOC;
            posTileSet.y = m->lvl->map[j][i] / TILE_MAX * TAILLE_BLOC;

            if(i>=0 && i<m->lvl->width)
            {
                SDL_BlitSurface(tile,&posTileSet,screen,&posTile);
            }
        }
    }

    if (maxx >= m->lvl->width - NB_BLOCS_LARGEUR/2)
    {
        end = imageLoad("sprites/game-over.jpg");
        posTile.x = (m->lvl->width - NB_BLOCS_LARGEUR/2 +1)*TAILLE_BLOC - m->xScroll;
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
            if(m->xScroll < (m->lvl->width+1)*TAILLE_BLOC-m->screenWidth)
                m->xScroll+= speed;
            break;

        case LEFT:
            if(m->xScroll > TAILLE_BLOC)
                m->xScroll-= speed;
            break;
        default: ;
    }
}

/**
 *\fn  Map *initMap(SDL_Surface *screen,char * level_name){
 *initialize the map
 *\param[in] screen game screen
 *\param[in] level_name lvl name
 *\return pointer on the map
 */
 Map *initMap(SDL_Surface *screen,char * level_name){
    Map *m;

    m = (Map *)malloc(sizeof(Map));
    if (m == NULL){
        perror("allocation error");
        exit(errno);
    }
    m->lvl=openLevel(level_name);
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
