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

    int continuer = 1;

    char level_name[MAX_SIZE_FILE_NAME];

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

    Sound *s = NULL;
    s =createSound();


    /*initialisation de l'écran*/
    screen = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);



    SDL_WM_SetCaption("Super Martin", NULL); //titre de la fenêtres

    SDL_ShowCursor(SDL_DISABLE); //efface la souris

    while (continuer) //main loop
    {

        if(menu(screen,&continuer,s))
        {
            if (menuLevel(screen,level_name,s))
                play(screen,level_name);
        }

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran

        SDL_Flip(screen);
    }

    freeSound(s);
    SDL_Quit();

    return 0;
}
