/*!
 * \file ennemies.h
 * \brief  character_list.c header
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef ENNEMIES_H_INCLUDED
#define ENNEMIES_H_INCLUDED

#include "character.h"

/**
 *\struct node
 * node for the ennemie list
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

 /*prototypes*/
  node * newNode(Character *c, node * n,node *p);

 void initList(list * l);

 int empty(list * l);
 int first(list * l);
 int last(list * l);
 int outOfList(list * l);

 void setOnFirst(list * l);
 void setOnLast(list * l);
 void next (list * l);
 void previous(list *l);
 Character *getCurrent (list * l);

 /*void printList(list * l);*/

 int insertFirst(list * l, Character *c);
 int insertLast(list * l, Character *c);
 int insertAfterCurrent(list * l, Character *c);
 int insertBeforeCurrent(list * l, Character *c);

 Character *deleteFirst(list * l);
 Character *deleteLast(list * l);
 Character *deleteCurrent(list * l);

 int find(list * l, Character *c);
 Character *deleteCharacter(list *l, Character *c);



#endif // ENNEMIES_H_INCLUDED
