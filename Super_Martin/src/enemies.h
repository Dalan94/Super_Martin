/*!
 * \file enemies.h
 * \brief  enemies.c header
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef ENEMIES_H_INCLUDED
#define ENEMIES_H_INCLUDED

#include "character.h"
#include "projectile.h"
#include "const.h"
#include "structures.h"


 /*prototypes*/
 /**
 *\fn node *newNode(enemy *c, node *n, node *p)
 *creates a new node
 *\param[in] c the character of the node
 *\param[in] n the next node
 *\param[in] p the previous node
 *\return a pointer on the created node
 */
  node * newNode(Character *c, node * n,node *p);

/**
 *\fn void initList (list *l)
 * initialize the enemy list
 *\param[out] l the list to be initalized
 */
 void initList(list * l);

/**
 *\fn int empty (list *l)
 * tests if the list is empty
 *\param[in] l the list to be tested
 *\return 1 if the list is empty, 0 if not
 */
 int empty(list * l);

 /**
 *\fn int first (list *l)
 * tests if the current node is the first node
 *\param[in] l the list to be tested
 *\return 1 if the current node is the first node, 0 if not
 */
 int first(list * l);

 /**
 *\fn int last (list *l)
 * tests if the current node is the last node
 *\param[in] l the list to be tested
 *\return 1 if the current node is the last node, 0 if not
 */
 int last(list * l);

 /**
 *\fn int outOfList (list *l)
 * tests if the current node is in the list
 *\param[in] l the list to be tested
 *\return 1 if the current node is in the list, 0 if not
 */
 int outOfList(list * l);

/**
 *\fn void setOnFirst (list *l)
 *set the current node on the first node
 *\param[out] l the list to be modified
 */
 void setOnFirst(list * l);

 /**
 *\fn void setOnLast (list *l)
 *set the current node on the last node
 *\param[out] l the list to be modified
 */
 void setOnLast(list * l);

 /**
 *\fn void next (list *l)
 *set the current node on its next node
 *\param[out] l the list to be modified
 */
 void next (list * l);

 /**
 *\fn void previous (list *l)
 *set the current node on its previous node
 *\param[out] l the list to be modified
 */
 void previous(list *l);

 /**
 *\fn enemy *getCurrent (list *l)
 *get the character of the current node
 *\param[in] l the list to be modified
 */
 Character *getCurrent (list * l);

/**
 *\fn int insertFirst (list *l, enemy *c)
 *insert a enemy as first node
 *\param[out] l the list in which the enemy has to be inserted
 *\param[in] c the enemy to be inserted
 *\return 1 if enemy inserted, 0 if failure
 */
 int insertFirst(list * l, Character *c);

 /**
 *\fn int insertLast (list *l, enemy *c)
 *insert a enemy as last node
 *\param[out] l the list in which the enemy has to be inserted
 *\param[in] c the enemy to be inserted
 *\return 1 if enemy inserted, 0 if failure
 */
 int insertLast(list * l, Character *c);

 /**
 *\fn int insertAfterCurrent (list *l, enemy *c)
 *insert a enemy just after the current node
 *\param[out] l the list in which the enemy has to be inserted
 *\param[in] c the enemy to be inserted
 *\return 1 if enemy inserted, 0 if failure
 */
 int insertAfterCurrent(list * l, Character *c);

 /**
 *\fn int insertBeforeCurrent (list *l, enemy *c)
 *insert a enemy just before the current node
 *\param[out] l the list in which the enemy has to be inserted
 *\param[in] c the enemy to be inserted
 *\return 1 if enemy inserted, 0 if failure
 */
 int insertBeforeCurrent(list * l, Character *c);

/**
 *\fn enemy *deleteFirst(list *l)
 *delete the first node
 *\param[out] l the list which has to be modified
 *\return the first node's enemy, NULL if empty list
 */
 Character *deleteFirst(list * l);

 /**
 *\fn enemy *deleteLast(list *l)
 *delete the last node
 *\param[out] l the list which has to be modified
 *\return the last node's enemy, NULL if empty list
 */
 Character *deleteLast(list * l);

 /**
 *\fn enemy *deleteCurrent(list *l)
 *delete the current node
 *\param[out] l the list which has to be modified
 *\return the current node's enemy, NULL if empty list
 */
 Character *deleteCurrent(list * l);

/**
 *\fn void createEnemy(char *spR,char *spL,int x,int y, list *l,int type)
 *creates an enemy and adds it to an enemies list
 *\param[in] spR right sprite address
 *\param[in] spL right sprite address
 *\param[in] x enemy's x location
 *\param[in] y enemy's y location
 *\param[out] l enemies list
 *\param[in] type the type of enemy
 */
void createEnemy(char *tile,int x,int y, list *l,int type);

/**
 *\fn void freeEnemies(list *l)
 *free all the enemies and the list
 *\param[out] l the enemy list
 */
void freeEnemies(list *l);

/**
 *\fn void blitEnemies(SDL_Surface *screen, list *l)
 *blit the enemies
 *\param[in,out] screen game screen
 *\param[in,out] l the enemy list
 */
void blitEnemies(SDL_Surface *screen, list *l,Map *m);

/**
 *\fn int collisionEnemy(Character *c,list *l,Map *m)
 *determine if there is a collision beteewen the player sprite and an enemy and deals with
 *\param[in,out] c the player
 *\param[in,out] l the enemy list, change the current node
 *\param[in] m the game map
 *\return 1 if there is a collision, 0 if not
 */
int collisionEnemy(Character *c,list *l,Map *m);

/**
 *\fn void moveEnemies(list *l, Map *m, list *p,projectilSet *ps, int launch)
 *make the enemies moving
 *\param[in,out] l the enemy list
 *\param[in] m the game map
 *\param[in,out] p the player list
 *\param[out] ps the projectile set
 *\param[in] launch if 1, canons can fire an rocket
 */
void moveEnemies(list *l, Map *m,list *p,projectileSet *ps, int *lanch);

/**
 *\fn int moveCharacterCol(Character *c,int direction,Map *m)
 *moves the character if it's hurt by an enemy
 *\param[in,out] c the character
 *\param[in] direction the direction of the movement
 *\param[in] m level map
 *\return 1 if character was moved without using the precise movement function, 0 if not
 */
int moveCharacterCol(Character *c,int move_left, int move_right,Map *m);

#endif // ENEMIES_H_INCLUDED
