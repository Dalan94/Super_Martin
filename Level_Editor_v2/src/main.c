/*!
 * \file main.c
 * \author Xavier COPONET, Glenn HERROU
 * \date 2014-03-18
 */

#include "game.h"
#include "const.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;

    int go = 1;

    char level_name[MAX_LENGTH_FILE_NAME] = "/home/glenn/GIT/Super_Martin/Super_Martin/level/test1.lvl";

    SDL_Init(SDL_INIT_VIDEO);

    /*  Initialization of the screen */

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    /*  Set the title of the window */

    SDL_WM_SetCaption("Super Martin : Level Editor", NULL);


    while (go) //main loop
    {



        play(screen,level_name);

        /*  Fill the screen with blank tiles */

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,TRANS_R,TRANS_G,TRANS_B)); //effacer l'écran

        /*  Display the screen */

        SDL_Flip(screen);
    }

    SDL_Quit();

    return 0;
}
