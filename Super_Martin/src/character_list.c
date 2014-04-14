/*!
 *\file character_list.c
 *\brief containe enemies list gestion function
 *\author Xavier COPONET
 *\date 2014-04-14
*/

#include "character_list.h"

/**
 *\fn node *newNode(Character *c, node *n, node *p)
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
 * initialize the ennemie list
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
	if(l->first==NULL) return 1;
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
	return l->current==NULL;

}

/**
 *\fn void setOnFirst (list *l)
 *set the current node on the first node
 *\param[out] l the list to be modified
 */
void setOnFirst (list *l)
{
	l->current=l->first;
}

/**
 *\fn void setOnLast (list *l)
 *set the current node on the last node
 *\param[out] l the list to be modified
 */
void 	setOnLast (list *l)
{
	l->current=l->last;
}

/**
 *\fn void next (list *l)
 *set the current node on its next node
 *\param[out] l the list to be modified
 */
void 	next (list *l)
{
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
 *\fn Character *getCurrent (list *l)
 *get the character of the current node
 *\param[in] l the list to be modified
 */

Character *getCurrent (list *l)
{
	return l->current->c;
}

/*void 	printList (list *l){
	int res;
	setOnFirst(l);

	printf("la liste :\n\n");
	while(!outOfList(l)){
		res=getCurrent(l);
		printf("%d\n",res);
		next(l);
	}
}*/


/**
 *\fn int insertFirst (list *l, Character *c)
 *insert a character as first node
 *\param[out] l the list in which the character has to be inserted
 *\param[in] c the character to be inserted
 *\return 1 if character inserted, 0 if failure
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
 *\fn int insertLast (list *l, Character *c)
 *insert a character as last node
 *\param[out] l the list in which the character has to be inserted
 *\param[in] c the character to be inserted
 *\return 1 if character inserted, 0 if failure
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
 *\fn int insertAfterCurrent (list *l, Character *c)
 *insert a character just after the current node
 *\param[out] l the list in which the character has to be inserted
 *\param[in] c the character to be inserted
 *\return 1 if character inserted, 0 if failure
 */
int insertAfterCurrent (list *l, Character *c)
{
	node *n=NULL;
	if(empty(l)) insertFirst(l,c);
	n = newNode(c,l->current->next,l->current->previous);
	if(n==NULL) return 0;

	(l->current)->next = n;

	return 1;
}

/**
 *\fn int insertBeforeCurrent (list *l, Character *c)
 *insert a character just before the current node
 *\param[out] l the list in which the character has to be inserted
 *\param[in] c the character to be inserted
 *\return 1 if character inserted, 0 if failure
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
 *\fn Character *deleteFirst(list *l)
 *delete the first node
 *\param[out] l the list which has to be modified
 *\return the first node's character, NULL if empty list
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
		if(l->first == NULL)
			initList(l);
        l->first->previous = NULL;
		ret = n->c;
		free((void *)n);
		return ret;
	}
}

/**
 *\fn Character *deleteLast(list *l)
 *delete the last node
 *\param[out] l the list which has to be modified
 *\return the last node's character, NULL if empty list
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
 *\fn Character *deleteCurrent(list *l)
 *delete the current node
 *\param[out] l the list which has to be modified
 *\return the current node's character, NULL if empty list
 */

Character *deleteCurrent (list *l)
{
	if(empty(l)){
		printf("Error : trying to delete a node in an empty list\n");
		return NULL;
	}else{
		Character *ret;
		node *n=l->current;
		if(first(l)) {deleteFirst(l); return 0;}
		if(last(l)) {deleteLast(l); return 0;}

        l->current->previous->next = l->current->next;
        l->current->next->previous = l->current->previous;

		ret=n->c;
		free((void *) n);
		return ret;
	}
}

/**
 *\fn int find(list *l, Character *c)
 *tells if the value is in the character is in the list
 *\param[in] l the list to be tested
 *\param[in] c the character which is sought for
 *\return 1 if the character is the list, 0 if not
 */

int find(list *l, Character *c)
{
    if(empty(l))
        return 0;
	setOnFirst(l);

	while(!outOfList(l)){
		if(l->current->c->label == c->label) return 1;
		next(l);
	}
	return 0;
}

/**
 *\fn Character *deleteCharacter(list *l)
 *delete the node containing the character
 *\param[out] l the list which has to be modified
 *\param[in] c the character which is has to be deleted
 *\return the character,NULL if the character isn't in the list
*/
Character *deleteCharacter(list *l, Character *c)
{
    if(!find(l,c))
        return NULL;
    setOnFirst(l);

    while(!outOfList(l)){
		if(l->current->c->label == c->label) {
            return deleteCurrent(l);
		}

		next(l);
	}
	return NULL;
}

