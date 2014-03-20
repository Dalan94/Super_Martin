/*!
 * \file map.c
 * \brief contient les fonction liées au chargement et à l'affichage de la carte
 * \author Xavier COPONET
 * \date 2014-03-18
 */

#include "map.h"

/**
 *\fn void updateScreenMap(SDL_Surface *screen, Map *m,char *tileset)
 *met à jour l'écran avec les données de la carte (ignore les personnages)
 *\param[in,out] screen of the game
 *\param[in] Map *m The map
 *\param[in] tileset lvl tileset
 */
void updateScreenMap(SDL_Surface *screen, Map *m, char *tileset){
    SDL_Surface *tile;
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

    SDL_FreeSurface(tile);

}

/**
 *\fn void scrolling(Map *m,int direction,float speed)
 *effectue un scrolling
 *\param[in,out] map Le niveau à gérer
 *\param[in] direction La direction de scrolling
 *\param[in] speed la vitesse de scrolling
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
 *initialise la carte
 *\param[in] screen l'écran de jeu
 *\param[in] level_name le nom du niveau
 *\return un pointeur sur la carte initialisée
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
  *désalloue la carte
  *\param[in,out] m la carte
  */
void freeMap(Map *m){
    closeLevel(m->lvl);
    free((void *)m);
}
