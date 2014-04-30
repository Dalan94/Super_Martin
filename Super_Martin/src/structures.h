/**
 *\file structures.h
 *containe the definition of some structures
 *\author X.COPONET
 *\date 2014-04-15
 */

#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
#include <SDL/SDL.h>

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
    int isJumping; /*! 0 when not jumping, height remaning between character and max height if jumping*/
    int life; /*! character life, 100 when full life, 0 when dead*/
    int countStars; /*! character points with caught stars */
    int isHurt; /*! indicate if the character was hurt recently*/
    int isFalling; /*! indicate if the character is falling*/
    int moving;/*! indicate the number of moving*/


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


#endif // STRUCTURES_H_INCLUDED
