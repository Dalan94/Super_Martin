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
#include "menu_option.h"
#include "menu_level.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;

    int go = 1;

    char level_name[MAX_SIZE_FILE_NAME];

    /*sound*/
    Sound *sound_system;
    sound_system = createSound();
    soundVolume(sound_system,1,0); /*mute music*/
    soundVolume(sound_system,0,0); /*mute effects*/

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

    /*initialisation de l'écran*/
    screen = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);



    SDL_WM_SetCaption("Super Martin", NULL); //titre de la fenêtres

    SDL_ShowCursor(SDL_DISABLE); //efface la souris

    while (go) //main loop
    {

        if(titleMenu(screen,&go,sound_system))
        {
            switch(mainMenu(screen,&go,sound_system))
            {
                case -1:
                    break;
                case 0:
                    if (menuLevel(screen,level_name,sound_system,&go))
                        while(play(screen,level_name,sound_system,&go));
                    break;
                case 1:
                    switch(optionMenu(screen,&go,sound_system))
                    {
                        case -1:
                            break;
                        case 0:
                            soundOptions(screen,&go,sound_system);
                            break;
                        default:;
                    }
                default: ;
            }

        }

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran

        SDL_Flip(screen);
    }


    freeSound(sound_system);

    SDL_Quit();

    return 0;
}
