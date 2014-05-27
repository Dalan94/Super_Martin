#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "const.h"

/**
 *\struct Input
 * The input structure
 */
 typedef struct
{
	char key[SDLK_LAST]; /*!< all the keyboard keys : 1 the key is pushed, 0 isn't */
	char mouse[6]; /*!< all the mouse buttons : 1 the button is pushed, 0 isn't */
	int mouseX; /*!< The x coordinate of the mouse */
	int mouseY; /*!< The y coordinate of the mouse */
	int quit; /*!< is 1 is the SDL_QUIT event happens */
} Input;

/**
 *\struct Cursor
 * The cursor structure
 */
typedef struct
{
    int x; /*!< The x coordinate*/
    int y; /*!< The y coordinate */
    char tileID; /*!< The tile ID*/
}Cursor;

/**
 *\struct Level
 * The level structure
 */
typedef struct
{
    unsigned char**map; /*!< The map*/
    int width; /*!< The width*/
    int height; /*!< The height*/
    int timer_level; /*!< The timer level*/
    char tileSet[MAX_LENGTH_FILE_NAME]; /*!< The tilset*/
    char background[MAX_LENGTH_FILE_NAME]; /*!< The background*/
    char music[MAX_LENGTH_FILE_NAME]; /*!< The music*/
}Level;

/**
 *\struct Map
 * The map structure
 */
typedef struct
{
    Level *lvl; /*!< The level*/
    int xScroll; /*!< The xscroll*/
    int screenWidth; /*!< The Screen width*/
    int screenHeight; /*!< The screen height*/
}Map;



#endif // STRUCTURES_H_INCLUDED
