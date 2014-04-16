#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct{
    int label; /*! the character label, to indentify the character*/
    SDL_Surface *spriteR,*spriteL;

    SDL_Rect location;
    float dirX,dirY;

    int isRight; /*! indicate the character's diraction (1 right, 0 left)*/
    int isOnGround; /*! indicate if the character is on the ground*/
    int isJumping; /*! 0 when not jumping, height remaning between character and max height if jumping*/
    int life; /*! character life, 100 when full life, 0 when dead*/
    int isHurt; /*! indicate if the character was hurt recently*/
    int isFalling; /*! indicate if the character is falling*/

    int x1,x2; /*! left and right deplacement limits for pnj */
    int saveX; /*! save the position of the pnj to know if he is blocked at the next loop iteration*/
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
