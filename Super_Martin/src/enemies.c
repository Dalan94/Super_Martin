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

void createEnemy(char *tile,int x,int y, list *l)
{
    Character *e;
    e = createrCharacter(tile, x, y,1);
    if(e == NULL)
    {
        perror("allocation error");
        exit(errno);
    }
    insertLast(l,e);
}

/**
 *\fn void freeEnemies(list *l)
 *free all the enemies and the list
 *\param[out] l the enemy list
 */
void freeEnemies(list *l)
{
    setOnFirst(l);
    while(!outOfList(l))
    {
        deleteCurrent(l);
        next(l);
    }
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
 *\fn int collisionEnemy(Character *c,list *l)
 *determine if there is a collision beteewen the player sprite and an enemy and deals with
 *\param[in,out] c the player
 *\param[in,out] l the enemy list, change the current node
 *\return 1 if there is a collision, 0 if not
 */
int collisionEnemy(Character *c,list *l,Map *m)
{

    int ret = 0;
    int ret1 = 1;

    setOnFirst(l);
    if(l==NULL)
        return 0;

    while(!outOfList(l))
    {
        switch(collisionSprite(c->location,l->current->c->location))
        {
            case 1:
                if(!(c->isNpc))
                {
                    if(!c->isHurt)
                    {
                        c->life -= 50;
                        c->isHurt = 50;
                        c->countStars -=2;
                    }


                    if(c->isRight)
                    {
                        ret1 = moveCharacterCol(c,1,0,m);
                        moveCharacterCol(l->current->c,0,1,m);
                    }
                    else
                    {
                        ret1 = moveCharacterCol(c,0,1,m);
                        moveCharacterCol(l->current->c,1,0,m);
                    }
                    l->current->c->isRight ^= 1;
                    l->current->c->saveX = l->current->c->location.x;
                }
                else
                {
                    if(!l->current->c->isHurt)
                    {
                        l->current->c->life -= 50;

                        l->current->c->countStars -=2;

                        l->current->c->isHurt = 50;
                    }


                    if(c->isRight)
                    {
                        ret1 = moveCharacterCol(l->current->c,0,1,m);
                        moveCharacterCol(c,1,0,m);
                    }
                    else
                    {
                        ret1 = moveCharacterCol(l->current->c,1,0,m);
                        moveCharacterCol(c,0,1,m);
                    }
                    c->isRight ^= 1;
                    c->saveX = c->location.x+10;

                }
                ret = 1;
                break;

            case 2:
                if(!c->isNpc)
                {
                    c->dirY = -(JUMP_HEIGHT/2);
                    deleteCurrent(l);
                    ret = 1;
                    c->countStars +=2;

                }
                break;

            case 0: ;

            default: ;
        }
        next(l);
    }

    return ret;
}


/**
 *\fn void moveEnemies(list *l, Map *m)
 *make the enemies moving
 *\param[in,out] l the enemy list
 *\param[in] m the game map
 */
void moveEnemies(list *l, Map *m, list *p)
{
    int ret = 0;
    setOnFirst(l);
    while(!outOfList(l))
    {
        if(l->current->c->location.x == l->current->c->saveX || checkFall(l->current->c,m))
            l->current->c->isRight ^= 1;
        l->current->c->saveX = l->current->c->location.x;

        if(l->current->c->isRight)
           ret = moveCharacter(l->current->c,0,1,0,m,2,p,NULL,NULL);

        else if(!l->current->c->isRight)
           ret = moveCharacter(l->current->c,1,0,0,m,2,p,NULL,NULL);

        if((l->current->c->location.y + l->current->c->tile->h/NB_TILE_MARYO_HEIGHT) >= m->lvl->height*TILE_SIZE-1)
            deleteCurrent(l);
        next(l);
    }
}

/**
 *\fn int moveCharacterCol(Character *c,int direction,Map *m,float speed)
 *moves the character if it's hurt by an enemy
 *\param[in,out] c the character
 *\param[in] direction the direction of the movement
 *\param[in] m level map
 *\return 1 if character was moved without using the precise movement function, 0 if not
 */

int moveCharacterCol(Character *c,int move_left, int move_right,Map *m)
{
    if(!c->isNpc)
        return moveCharacter(c,move_left,move_right,0,m,50,NULL,NULL,NULL);
    else
        return moveCharacter(c,move_left,move_right,0,m,5,NULL,NULL,NULL);

}


/* ******************************** */
/* gestion des listes*/
/**
 *\fn node *newNode(enemy *c, node *n, node *p)
 *creates a new node
 *\param[in] c the character of the node
 *\param[in] n the next node
 *\param[in] p the previous node
 *\return a pointer on the created node
 */

node * 	newNode (Character *c, node *n, node *p)
{
	node *ptr=(node *) malloc(sizeof(node));
	ptr->c=c;
	ptr->next=n;
	ptr->previous = p;
	return ptr;
}

/**
 *\fn void initList (list *l)
 * initialize the enemy list
 *\param[out] l the list to be initalized
 */
void initList (list *l)
{
	l->first=NULL;
	l->current=NULL;
	l->last=NULL;
}

/**
 *\fn int empty (list *l)
 * tests if the list is empty
 *\param[in] l the list to be tested
 *\return 1 if the list is empty, 0 if not
 */
int	empty (list *l)
{
	if(l==NULL || l->first==NULL) return 1;
	return 0;
}

/**
 *\fn int first (list *l)
 * tests if the current node is the first node
 *\param[in] l the list to be tested
 *\return 1 if the current node is the first node, 0 if not
 */
int 	first (list *l){
	if(l->current==l->first) return 1;
	return 0;
}

/**
 *\fn int last (list *l)
 * tests if the current node is the last node
 *\param[in] l the list to be tested
 *\return 1 if the current node is the last node, 0 if not
 */
int last (list *l){
	if(l->current==l->last) return 1;
	return 0;
}

/**
 *\fn int outOfList (list *l)
 * tests if the current node is in the list
 *\param[in] l the list to be tested
 *\return 1 if the current node is in the list, 0 if not
 */
int outOfList (list *l){
	if(l!=NULL)
        return l->current==NULL;
    return 1;
}

/**
 *\fn void setOnFirst (list *l)
 *set the current node on the first node
 *\param[out] l the list to be modified
 */
void setOnFirst (list *l)
{
    if(l!=NULL)
        l->current=l->first;
}

/**
 *\fn void setOnLast (list *l)
 *set the current node on the last node
 *\param[out] l the list to be modified
 */
void setOnLast (list *l)
{
	l->current=l->last;
}

/**
 *\fn void next (list *l)
 *set the current node on its next node
 *\param[out] l the list to be modified
 */
void next (list *l)
{
    if(l!=NULL && !empty(l) && !outOfList(l))
        l->current = (l->current->next);
}

/**
 *\fn void previous (list *l)
 *set the current node on its previous node
 *\param[out] l the list to be modified
 */
void previous (list *l)
{
	l->current = (l->current->previous);
}

/**
 *\fn enemy *getCurrent (list *l)
 *get the character of the current node
 *\param[in] l the list to be modified
 */

Character *getCurrent (list *l)
{
	return l->current->c;
}


/**
 *\fn int insertFirst (list *l, enemy *c)
 *insert a enemy as first node
 *\param[out] l the list in which the enemy has to be inserted
 *\param[in] c the enemy to be inserted
 *\return 1 if enemy inserted, 0 if failure
 */
int insertFirst (list *l, Character *c)
{
	node *first=newNode(c,l->first,NULL);
	if(first==NULL) return 0;
	if(empty(l)) l->last = l->current = first;
	l->first = first;

	return 1;
}

/**
 *\fn int insertLast (list *l, enemy *c)
 *insert a enemy as last node
 *\param[out] l the list in which the enemy has to be inserted
 *\param[in] c the enemy to be inserted
 *\return 1 if enemy inserted, 0 if failure
 */
int insertLast (list *l, Character *c)
{
	node *last=NULL;
	if(empty(l)) insertFirst(l,c);
	last = newNode(c,NULL,l->last);
	if(last==NULL) return 0;


	l->last->next = last;
	l->last = last;

	return 1;
}

/**
 *\fn int insertAfterCurrent (list *l, enemy *c)
 *insert a enemy just after the current node
 *\param[out] l the list in which the enemy has to be inserted
 *\param[in] c the enemy to be inserted
 *\return 1 if enemy inserted, 0 if failure
 */
int insertAfterCurrent (list *l, Character *c)
{
	node *n=NULL;
	if(empty(l))
    {
        insertFirst(l,c);
        return 1;
	}
	n = newNode(c,l->current->next,l->current->previous);
	if(n==NULL) return 0;

	(l->current)->next = n;

	return 1;
}

/**
 *\fn int insertBeforeCurrent (list *l, enemy *c)
 *insert a enemy just before the current node
 *\param[out] l the list in which the enemy has to be inserted
 *\param[in] c the enemy to be inserted
 *\return 1 if enemy inserted, 0 if failure
 */

int insertBeforeCurrent (list *l, Character *c)
{
	node *n=NULL;
	if(empty(l)) insertFirst(l,c);
	n = newNode(c,l->current,l->current->previous->previous);
	if(n==NULL) return 0;

	(l->current->previous->next) = n;
	(l->current->previous) = n;

	return 1;
}

/**
 *\fn enemy *deleteFirst(list *l)
 *delete the first node
 *\param[out] l the list which has to be modified
 *\return the first node's enemy, NULL if empty list
 */
Character *deleteFirst (list *l)
{
	if(empty(l)){
		printf("Error : trying to delete a node in an empty list\n");
		return NULL;
	}
	else{
		Character *ret;
		node *n = l->first;
		l->first = n->next;

		if(n->next == NULL)
            initList(l);
        else
            l->first->previous = NULL;
		ret = n->c;
		free((void *)n);
		return ret;
	}
}

/**
 *\fn enemy *deleteLast(list *l)
 *delete the last node
 *\param[out] l the list which has to be modified
 *\return the last node's enemy, NULL if empty list
 */
Character *deleteLast (list *l)
{
	if(empty(l)){
		printf("Error : trying to delete a node in an empty list\n");
		return NULL;
	}else{
		Character *ret;
		node *n=l->last;

		l->last = l->last->previous;
		l->last->next = NULL;
		ret=n->c;
		free((void *) n);
		return ret;
	}
}

/**
 *\fn enemy *deleteCurrent(list *l)
 *delete the current node
 *\param[out] l the list which has to be modified
 *\return the current node's enemy, NULL if empty list
 */

Character *deleteCurrent (list *l)
{
	if(empty(l)){
		printf("Error : trying to delete a node in an empty list\n");
		return NULL;
	}else{
		Character *ret;
		node *n=l->current;
		if(first(l)) {return deleteFirst(l); }
		if(last(l)) {return deleteLast(l);}

        l->current->previous->next = l->current->next;
        l->current->next->previous = l->current->previous;

		ret=n->c;
		free((void *) n);
		return ret;
	}
}




