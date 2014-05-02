#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "const.h"

 typedef struct
{
	char key[SDLK_LAST];
	char mouse[6];
	int mouseX;
	int mouseY;
	int quit;
} Input;

typedef struct
{

    int x;
    int y;
    char tileID;
}Cursor;

typedef struct{
    unsigned char**map;
    int width;
    int height;
    int timer_level;
    char tileSet[MAX_LENGTH_FILE_NAME];
    char background[MAX_LENGTH_FILE_NAME];
    char music[MAX_LENGTH_FILE_NAME];
}Level;

typedef struct{
    Level *lvl;
    int xScroll;
    int screenWidth,screenHeight;
}Map;



#endif // STRUCTURES_H_INCLUDED
