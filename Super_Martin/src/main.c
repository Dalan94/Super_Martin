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
#include "option.h"
#include "player.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;

    int go = 1;
    int ret,ret1, ret2 = 0, ret3;

    char level_name[MAX_SIZE_FILE_NAME];
    char player_name[MAX_SIZE_FILE_NAME];

    /*sound*/
    Sound *sound_system;
    sound_system = createSound();

    /*config clavier*/
    SDLKey kc[4];

    /*chargement des configuration */
    loadOptions(".conf",sound_system,kc);

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

    /*initialisation de l'écran*/
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);



    SDL_WM_SetCaption("Super Martin", NULL); //titre de la fenêtres

    SDL_ShowCursor(SDL_DISABLE); //efface la souris

    while (go) //main loop
    {

        if(titleMenu(screen,&go,sound_system))
        {
            while( (ret3 = menuPlayers(screen, player_name, &go, sound_system)) != -1)
            {
                switch(ret3)
                {
                    case -1:
                        break;
                    case 2  :
                        ret2 = newPlayer(screen, player_name, sound_system, &go);
                        if(ret2 == 1);
                        else
                            break;

                    case 1  :

                        while((ret1 = mainMenu(screen,&go,sound_system, player_name)) != -1)
                        {
                            switch(ret1)
                            {
                                case -1:
                                    break;
                                case 0:
                                    if (menuLevel(screen,level_name,sound_system,&go))
                                        while(play(screen,level_name,sound_system,&go,kc));
                                    break;
                                case 1:
                                    while((ret = optionMenu(screen,&go,sound_system,kc)) != -1)
                                        switch(ret)
                                        {
                                            case -1:
                                                break;
                                            case 0:
                                                soundOptions(screen,&go,sound_system);
                                                break;
                                            case 1:
                                                keyBoardOptions(screen,&go,kc);
                                                break;
                                            default:;
                                        }
                                default: ;
                            }
                        }

                    default : ;

                }
            }

        }

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran

        SDL_Flip(screen);
    }


    freeSound(sound_system);

    SDL_Quit();

    return 0;
}
