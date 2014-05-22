/*!
 *\file enemies.c
 *\brief  containe enemies gestion function
 *\author Xavier COPONET
 *\date 2014-04-14
*/

#include "enemies.h"

void createEnemy(char *tile,int x,int y, list *l, int type)
{
    Character *e;
    e = createCharacter(tile, x, y,type, 0, 0, 0);
    if(e == NULL)
    {
        perror("allocation error");
        exit(errno);
    }
    insertLast(l,e);
}


void freeEnemies(list *l)
{
    setOnFirst(l);
    while(!outOfList(l))
    {
        deleteCurrent(l);
        next(l);
    }
}


void blitEnemies(SDL_Surface *screen, list *l,Map *m)
{
    setOnFirst(l);

    while(!outOfList(l))
    {
        if(l->current->c->isNpc != 2 && l->current->c->isNpc != 3 && l->current->c->isNpc != 4)
            blitCharacter(screen,l->current->c,m);
        next(l);
    }
}


int collisionEnemy(Character *c,list *l,Map *m)
{

    int ret = 0;
    int ret1 = 1;

    setOnFirst(l);
    if(l==NULL)
        return 0;

    while(!outOfList(l))
    {
        if(l->current->c->isNpc != 2 && l->current->c->isNpc != 3)
        {
            switch(collisionSprite(c->location,l->current->c->location))
            {
                case 1:
                    if(!(c->isNpc))
                    {
                        if(!c->isHurt && l->current->c->isNpc != 2)
                        {
                            c->hp -= 50;
                            c->isHurt = 50;
                        }

                        if(l->current->c->isNpc != 2)
                        {
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
                    }
                    else
                    {
                        if(!l->current->c->isHurt && l->current->c->isNpc != 2)
                        {
                            l->current->c->hp -= 50;

                            l->current->c->isHurt = 50;
                        }

                        if(l->current->c->isNpc != 2)
                        {
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
                    }
                    ret = 1;
                    break;

                case 2:
                    if(!c->isNpc && l->current->c->isNpc != 2)
                    {
                        c->dirY = -(JUMP_HEIGHT/2);
                        deleteCurrent(l);
                        ret = 1;
                    }
                    break;
                case 3:
                    if(!c->isNpc && l->current->c->isNpc != 2)
                    {
                        c->dirY = -(JUMP_HEIGHT/2);
                        deleteCurrent(l);
                        ret = 1;
                    }
                    break;

                case 0: ;

                default: ;
            }
        }
        next(l);
    }

    return ret;
}



void moveEnemies(list *l, Map *m, list *p,projectileSet *ps,int *launch)
{
    int ret = 0;
    float s;
    s = 2;
    setOnFirst(l);
    while(!outOfList(l))
    {
        switch(l->current->c->isNpc)
        {
            case 2:
                if(*launch)
                {
                    createProjectile(ps,"rocket",LEFT,l->current->c->location.x,l->current->c->location.y+16,1);
                }
                break;
            case 3:
                if(*launch)
                {
                    createProjectile(ps,"rocket",RIGHT,l->current->c->location.x+32,l->current->c->location.y+16,1);
                }
                break;
            case 4:
                if(*launch)
                {
                    createProjectile(ps,"rocket",RIGHT,l->current->c->location.x+32,l->current->c->location.y+16,1);
                    createProjectile(ps,"rocket",LEFT,l->current->c->location.x,l->current->c->location.y+16,1);
                }
                break;
            default:
                if(l->current->c->location.x == l->current->c->saveX || checkFall(l->current->c,m,NULL))
                    l->current->c->isRight ^= 1;
                l->current->c->saveX = l->current->c->location.x;

                if(l->current->c->isRight)
                    ret = moveCharacter(l->current->c,0,1,0,m,&s,p,NULL,NULL);

                else if(!l->current->c->isRight)
                    ret = moveCharacter(l->current->c,1,0,0,m,&s,p,NULL,NULL);
                break;
        }



        if((l->current->c->isNpc != 2 && l->current->c->isNpc != 3 && l->current->c->isNpc != 4) &&
            (l->current->c->location.y + l->current->c->tile->h/NB_TILE_MARYO_HEIGHT) >= m->lvl->height*TILE_SIZE-1)
            deleteCurrent(l);
        next(l);
    }
    if(*launch)
        *launch = 0;
}



int moveCharacterCol(Character *c,int move_left, int move_right,Map *m)
{
    float s;
    if(!c->isNpc)
    {
        s = 25;
        return moveCharacter(c,move_left,move_right,0,m,&s,NULL,NULL,NULL);
    }
    else
    {
        s =  5;
        return moveCharacter(c,move_left,move_right,0,m,&s,NULL,NULL,NULL);
    }

}


/* ******************************** */
/* list gestion                     */
/* ******************************** */


node * 	newNode (Character *c, node *n, node *p)
{
	node *ptr=(node *) malloc(sizeof(node));
	ptr->c=c;
	ptr->next=n;
	ptr->previous = p;
	return ptr;
}


void initList (list *l)
{
	l->first=NULL;
	l->current=NULL;
	l->last=NULL;
}


int	empty (list *l)
{
	if(l==NULL || l->first==NULL) return 1;
	return 0;
}


int 	first (list *l){
	if(l->current==l->first) return 1;
	return 0;
}


int last (list *l){
	if(l->current==l->last) return 1;
	return 0;
}


int outOfList (list *l){
	if(l!=NULL)
        return l->current==NULL;
    return 1;
}


void setOnFirst (list *l)
{
    if(l!=NULL)
        l->current=l->first;
}


void setOnLast (list *l)
{
	l->current=l->last;
}


void next (list *l)
{
    if(l!=NULL && !empty(l) && !outOfList(l))
        l->current = (l->current->next);
}


void previous (list *l)
{
	l->current = (l->current->previous);
}


Character *getCurrent (list *l)
{
	return l->current->c;
}


int insertFirst (list *l, Character *c)
{
	node *first=newNode(c,l->first,NULL);
	if(first==NULL) return 0;
	if(empty(l)) l->last = l->current = first;
	l->first = first;

	return 1;
}


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




