#include "jeu.h"
#include "const.h"
#include "menu.h"
#include "menu_level.h"
#include "sound.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;

    int continuer = 1;

    char level_name[TAILLE_MAX_NOM_FICHIER];

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

    Sound *s = NULL;
    s =createSound();


    /*initialisation de l'�cran*/
    screen = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);



    SDL_WM_SetCaption("Super Martin", NULL); //titre de la fen�tres

    SDL_ShowCursor(SDL_DISABLE); //efface la souris

    while (continuer) //main loop
    {

        if(menu(screen,&continuer,s))
        {
            if (menuLevel(screen,level_name,s))
                jouer(screen,level_name);
        }

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'�cran

        SDL_Flip(screen);
    }

    SDL_Quit();

    return 0;
}
