#include "jeu.h"
#include "const.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;

    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);



    /*initialisation de l'écran*/
    screen = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);



    SDL_WM_SetCaption("Super Princess Peach", NULL); //titre de la fenêtres

    SDL_ShowCursor(SDL_DISABLE); //efface la souris


    while (continuer) //main loop
    {

        if(menu(screen,&continuer))
            jouer(screen,"level/test.lvl");

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran

        SDL_Flip(screen);
    }

    SDL_Quit();

    return 0;
}
