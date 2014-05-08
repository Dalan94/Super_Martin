/**
 *\file structures.h
 *containe the definition of some structures
 *\author X.COPONET
 *\date 2014-04-15
 */

#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
#include <SDL/SDL.h>
#include "const.h"

/**
 *\struc Character
 *the game characters : player and npc
 */
typedef struct
{
    int isNpc; /*! 1 if a npc, 0 if not*/
    SDL_Surface *tile;

    SDL_Rect location;
    int saveX,saveY; /*! save the position of the pnj to know if he is blocked at the next loop iteration*/
    float dirX,dirY;

    int isRight; /*! indicate the character's diraction (1 right, 0 left)*/
    int isOnGround; /*! indicate if the character is on the ground*/
    int doubleJump; /*! 0 when not jumping, 1 if made 1 jump (ie can make a double jump), 2 if have made double jump*/
    int life; /*! character life, 100 when full life, 0 when dead*/
    int countStars; /*! character points with caught stars */
    int isHurt; /*! indicate if the character was hurt recently*/
    int isFalling; /*! indicate if the character is falling*/
    int moving;/*! indicate the number of moving*/

    int OnPlatform; /*! indicates if the character is on the platform number x, -1 if not on a platform */


}Character;

/**
 *\struct node
 * node for the enemy list
 */

typedef struct node
{
     Character *c; /*! characater of the node*/
     struct node * next; /*! next node of the linked list*/
     struct node *previous; /*! previous node of the linked list*/
}node;

/**
 *\struct list
 *the linked list that stock the ennemies
 */

typedef struct
{
     node * first; /*! the list's first node*/
     node * current; /*! the list 's current node*/
     node * last; /*! the list 's last node*/
}list;

/**
 *\struct platform
 a mobile platform
 */
typedef struct
{
    SDL_Surface *sprite; /*! the platform's sprite */
    SDL_Rect location; /*! the platform location*/

    int xMin; /*! x low limit for deplacement */
    int xMax; /*! x hight limit for deplacement */
    int yMin; /*! y hight limit for deplacement */
    int yMax; /*! y hight limit for deplacement */

    int type; /*! 0 if horizontal movement, 1 if vertical */
    int direction; /*! the platform direction */

}platform;

/**
 *\struct platformSet
 *the set of the mobile platform
 */
typedef struct
{
    platform* tab[NB_PLATFORM_MAX]; /*! the platform set*/
    int nb; /*! the number of platform */
}platformSet;

/**
 *\struct projectile
 *a projectile structure
 */
typedef struct
{
    SDL_Surface *sprite; /*! the platform's sprite */
    SDL_Rect location; /*! the platform location*/

    int direction; /*! the platform direction */
}projectile;

/**
 *\struct projectileSet
 *the set of the projectiles
 */
typedef struct
{
    projectile* tab[NB_PROJECTILE_MAX]; /*! the projectile set*/
    int nb; /*! the number of projectiles on the map */
    int projectileThrown; /*! indicates if a projectile has been thrown and the key wasn't released yet */
}projectileSet;

#endif // STRUCTURES_H_INCLUDED
