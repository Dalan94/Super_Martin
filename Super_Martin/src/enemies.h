/*!
 * \file enemies.h
 * \brief  enemies.c header
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef ENEMIES_H_INCLUDED
#define ENEMIES_H_INCLUDED

#include "character.h"
#include "const.h"

/**
 *\struct enemy
 *"Inheritance" of the character structure
 */
typedef struct
{
    Character *c; /*! the enemy*/
    int x1; /*! the enemy left deplacement limit */
    int x2; /*! the enemy right deplacement limit */
} enemy;

/**
 *\struct node
 * node for the enemy list
 */

typedef struct node
{
     enemy *c; /*! characater of the node*/
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

 /*prototypes*/
  node * newNode(enemy *c, node * n,node *p);

 void initList(list * l);

 int empty(list * l);
 int first(list * l);
 int last(list * l);
 int outOfList(list * l);

 void setOnFirst(list * l);
 void setOnLast(list * l);
 void next (list * l);
 void previous(list *l);
 enemy *getCurrent (list * l);

 /*void printList(list * l);*/

 int insertFirst(list * l, enemy *c);
 int insertLast(list * l, enemy *c);
 int insertAfterCurrent(list * l, enemy *c);
 int insertBeforeCurrent(list * l, enemy *c);

 enemy *deleteFirst(list * l);
 enemy *deleteLast(list * l);
 enemy *deleteCurrent(list * l);


void createEnemy(char *spR,char *spL,int x,int y, list *l,int x1, int x2);
void blitEnnemies(SDL_Surface *screen, list *l,Map *m);
int collisionEnemy(Character *c,list *l);
void moveEnemies(list *l, Map *m);

#endif // ENEMIES_H_INCLUDED
