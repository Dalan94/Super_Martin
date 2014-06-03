/**
 *\file structures.h
 * contain the definition of some structures
 *\author X.COPONET
 *\date 2014-04-15
 */

#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
#include <SDL/SDL.h>
#include "const.h"

/**
 *\struct Character
 *the game characters : player and npc
 */
typedef struct
{
    int isNpc; /*!< the type of npc, 0 if not a npc,*/

    SDL_Surface *tile; /*!< the tile set of the character */

    SDL_Rect location; /*!< the location of the character */
    int saveX; /*!< save the position of the pnj to know if he is blocked at the next loop iteration*/
    int saveY; /*!< save the position of the pnj to know if he is blocked at the next loop iteration*/
    float dirX; /*!< the direction vectors of the character */
    float dirY; /*!< the direction vectors of the character */

    int isRight; /*!< indicate the character's diraction (1 right, 0 left)*/
    int isOnGround; /*!< indicate if the character is on the ground*/
    int doubleJump; /*!< 0 when not jumping, 1 if made 1 jump (ie can make a double jump), 2 if have made double jump*/
    int wallJump; /*!< indicates if can do wall jump, 0 don't, 1 wall at right, 2 wall at left */

    int hp; /*!< character hit points, dead when 0*/
    int hpMax; /*!< The HP max*/
    int nbLifes; /*!< nb of the character has */
    int countStars; /*!< character points with caught stars */
    int isHurt; /*!< indicate if the character was hurt recently*/
    int isFalling; /*!< indicate if the character is falling*/
    int moving;/*!< indicate the number of moving*/

    int OnPlatform; /*!< indicates if the character is on the platform number x, -1 if not on a platform */

    int nbProjectile; /*!< indicates the number of projectiles the character has */


}Character;

/**
 *\struct Player
 *The player
 */

typedef struct
{
    int levelMax; /*!< The level max*/
    int nbProjectile; /*!< The number of projectile*/
    int nbLifes; /*!< The number of life*/
    int nbCoins; /*!< The number of coins*/
} Player;

/**
 *\struct node
 * node for the enemy list
 */
typedef struct node
{
     Character *c; /*!< characater of the node*/
     struct node * next; /*!< next node of the linked list*/
     struct node *previous; /*!< previous node of the linked list*/
}node;

/**
 *\struct list
 *the linked list that stock the ennemies
 */
typedef struct
{
     node * first; /*!< the list's first node*/
     node * current; /*!< the list 's current node*/
     node * last; /*!< the list 's last node*/
}list;

/**
 *\struct platform
 a mobile platform
 */
typedef struct
{
    SDL_Surface *sprite; /*!< the platform's sprite */
    SDL_Rect location; /*!< the platform location*/

    int xMin; /*!< x low limit for deplacement */
    int xMax; /*!< x hight limit for deplacement */
    int yMin; /*!< y hight limit for deplacement */
    int yMax; /*!< y hight limit for deplacement */

    int type; /*!< 0 if horizontal movement, 1 if vertical */
    int direction; /*!< the platform direction */
    int speed; /*!< platform speed */

}platform;

/**
 *\struct platformSet
 *the set of the mobile platform
 */
typedef struct
{
    platform* tab[MAX_NB_PLATFORM]; /*!< the platform set*/
    int nb; /*!< the number of platform */
}platformSet;

/**
 *\struct projectile
 *a projectile structure
 */
typedef struct
{
    SDL_Surface *sprite; /*!< the platform's sprite */
    SDL_Rect location; /*!< the platform location*/

    int direction; /*!< the platform direction */

    int fromNPC; /*!< indicates if the projectile
     belongs to the player (0) or to a npc */
}projectile;

/**
 *\struct projectileSet
 *the set of the projectiles
 */
typedef struct
{
    projectile* tab[MAX_NB_PROJECTILE]; /*!< the projectile set*/
    int nb; /*!< the number of projectiles on the map */
    int projectileThrown; /*!< indicates if a projectile has been
    thrown by the player and the key wasn't released yet */
}projectileSet;

/* lvl */
/**
 *\struct Level
 * The level structure
 */
typedef struct
{
    unsigned char**map; /*!< The map*/
    int width; /*!< The width*/
    int height; /*!< The height*/
    int timer_level; /*!< The timer level*/
    char tileSet[MAX_SIZE_FILE_NAME]; /*!< The tilset*/
    int tileSetUse; /*!< The tilset of the spring which is used*/
    char background[MAX_SIZE_FILE_NAME]; /*!< The background*/
    char music[MAX_SIZE_FILE_NAME]; /*!< The music*/
}Level;

/**
 *\struct Map
 * The map structure
 */
typedef struct
{
    Level *lvl; /*!< The level*/
    int xScroll; /*!< The xscroll*/
    int screenWidth; /*!< The Screen width*/
    int screenHeight; /*!< The screen height*/
}Map;

#endif // STRUCTURES_H_INCLUDED
