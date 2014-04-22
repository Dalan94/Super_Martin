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
#include "structures.h"


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


void createEnemy(char *spR,char *spL,int x,int y, list *l,int x1, int x2);
void blitEnnemies(SDL_Surface *screen, list *l,Map *m);
int collisionEnemy(Character *c,list *l,Map *m);
void moveEnemies(list *l, Map *m,list *p);

#endif // ENEMIES_H_INCLUDED
