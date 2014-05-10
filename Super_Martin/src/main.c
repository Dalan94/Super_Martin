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
#include "structures.h"
#include "input.h"

#include "player.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;

    int go = 1;
    int i;
    //SDL_Joystick *joystick; // on crée le joystick
    int ret,ret1, ret2 = 0, ret3, ret4;

    char level_name[MAX_SIZE_FILE_NAME];
    char player_name[MAX_SIZE_FILE_NAME];
    int nb_lvl;
    /*sound*/
    Sound *sound_system;
    sound_system = createSound();

    /*config clavier*/
    SDLKey kc[NB_KEY-1];

    /*input*/
    Input in;

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_JOYSTICK);

    Player *current_player;

    current_player = (Player *)malloc(sizeof(Player));

    current_player->levelMax = 8;
    //current_player->hpMax = 150;
    current_player->nbCoins = 90;
    current_player->nbLifes = 3;


    /*initialisation de l'écran*/
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    initInput(&in);

    /*chargement des configuration */
    loadSoundOptions("configuration/sound.conf",sound_system);


    SDL_WM_SetCaption("Super Martin", NULL); //titre de la fenêtres

    SDL_ShowCursor(SDL_DISABLE); //efface la souris

    while (go) //main loop
    {
        if(titleMenu(screen,&go,sound_system, &in))
        {

            while( (ret3 = menuPlayers(screen, player_name, &go, sound_system, &in)) != -1)
            {
                switch(ret3)
                {
                    case -1:
                        break;
                    case 2  :
                        ret2 = newPlayer(screen, player_name, sound_system, &go);
                        if(ret2 == 1)
                            save(screen, "save/.save", player_name, current_player, &go);
                        else
                            break;

                    case 1  :
                        loadPlayer("save/.save", player_name, current_player);
                        loadInputOptions(player_name,kc,&in);
                        while((ret1 = mainMenu(screen,&go,sound_system, player_name, &in)) != -1)
                        {
                            switch(ret1)
                            {
                                case -1:
                                    break;
                                case 0:

                                    while( (ret4 = menuLevel(screen,level_name,sound_system, player_name, current_player, &go, &nb_lvl, &in)) != -1)
                                    {
                                        while(play(screen,level_name,sound_system,&go,kc, &in, current_player, player_name, ret4+1, nb_lvl));
                                    }
                                    break;

                                case 1 :
                                    save(screen, "save/.save", player_name, current_player, &go);
                                    loadPlayer("save/.save", player_name, current_player);
                                    break;

                                case 2 :
                                    while((ret = optionMenu(screen,&go,sound_system,kc, &in)) != -1)
                                        switch(ret)
                                        {
                                            case -1:
                                                break;
                                            case 0:
                                                soundOptions(screen,&go,sound_system, &in);
                                                break;
                                            case 1:
                                                keyBoardOptions(screen,&go,kc,&in,player_name);
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

    freeInput(&in);
    SDL_Quit();

    return EXIT_SUCCESS;
}
