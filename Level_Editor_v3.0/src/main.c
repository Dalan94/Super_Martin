/**
 *\file main.c
 *\author Xavier COPONET
 *\date 2014-02-27
 */


#include "game.h"
#include "const.h"
#include "menu.h"
#include "menu_level.h"
#include "sound.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;

    int go = 1;
    int pos_cursor;
    char level_name[MAX_LENGTH_FILE_NAME];

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

    /*  Initialization of the screen */

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);


    /*  Setting of the window title */

    SDL_WM_SetCaption("Super Martin", NULL);


    while (go) //main loop
    {

        if(menu(screen, pos_cursor))
        {
            if(!pos_cursor)
            {
                if (menuLevel(screen,level_name))
                    play(screen,level_name);
            }
            else
            {
                pos_cursor = 0;
                if (menuTileSet(screen,pos_cursor))
                    play(screen, "../Super_Martin/level/empty.lvl");
            }
        }

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_Flip(screen);
    }

    SDL_Quit();

    return 0;
}
