/*!
 *\file enemies.c
 *\brief  containe enemies gestion function
 *\author Xavier COPONET
 *\date 2014-04-14
*/

#include "enemies.h"

/**
 *\fn void createEnemy(char *spR,char *spL,int x,int y, list *l)
 *creates an enemy and adds it to an enemies list
 *\param[in] spR right sprite address
 *\param[in] spL right sprite address
 *\param[in] x enemy's x location
 *\param[in] y enemy's y location
 *\param[out] l enemies list
 */

void createEnemy(char *spR,char *spL,int x,int y, list *l)
{
    Character *enemy = createrCharacter(spR,spL,x, y);
    if(enemy == NULL)
    {
        perror("allocation error");
        exit(errno);
    }

    insertAfterCurrent(l,enemy);
}


/**
 *\fn void blitEnemies(SDL_Surface *screen, list *l)
 *blit the enemies
 *\param[in,out] screen game screen
 *\param[in,out] l the enemy list
 */

void blitEnnemies(SDL_Surface *screen, list *l,Map *m)
{
    setOnFirst(l);

    while(!outOfList(l))
    {
        blitCharacter(screen,l->current->c,m);
        next(l);
    }
}

/**
 *\fn int collisionEnemy(SDL_Rect r,list *l)
 *determine if there is a collision beteewen the player sprite and an enemy
 *\param[in] r SDL_Rect corresponding to the sprite
 *\param[in] l the enemy list
 *\return 1 if there is a collision, 0 if not
 */
/*int collisionEnemy(SDL_Rect r,list *l)
{
    int i,j;
    int xmin,xmax,ymin,ymax;
    SDL_Rect test;
    test.h = test.w = TAILLE_BLOC;

    if(r.x+r.w > (m->lvl->width+1)*TAILLE_BLOC || r.x < TAILLE_BLOC || r.y+r.h >(m->lvl->height)*TAILLE_BLOC -1 || r.y<0)
        return 1; //test les limites du monde

    xmin =  (r.x) / TAILLE_BLOC -1;
    xmax =  (r.x + r.w )  / TAILLE_BLOC ;
    ymin = (r.y) / TAILLE_BLOC ;
    ymax =  (r.y + r.h ) / TAILLE_BLOC +1;

    for(i = xmin ; i< xmax ; i++){
        for (j=ymin ; j< ymax ; j++){
            if(m->lvl->map[j][i] != VOID){
                test.x = i*TAILLE_BLOC;
                test.y = j*TAILLE_BLOC;
                if(!(((r.x+r.w < test.x)
                    && (r.x > test.x+test.w))
                    && ((r.y+r.h <= test.y)
                    && (r.y >= test.y+test.h)))
                )
                    return 1;
            }
        }
    }

    return 0;
}*/
