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
#include "input.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;

    int go = 1;
    int ret,ret1;
    int i;
    //SDL_Joystick *joystick; // on crée le joystick

    char level_name[MAX_SIZE_FILE_NAME];

    /*sound*/
    Sound *sound_system;
    sound_system = createSound();

    /*config clavier*/
    SDLKey kc[4];

    /*input*/
    Input in;

    /*chargement des configuration */
    loadOptions(".conf",sound_system,kc);

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_JOYSTICK);

    /*initialisation de l'écran*/
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    initInput(&in);

    SDL_WM_SetCaption("Super Martin", NULL); //titre de la fenêtres

    SDL_ShowCursor(SDL_DISABLE); //efface la souris


//    joystick = SDL_JoystickOpen(0); // on l'assigne au numéro 0
//
//    printf("\nIl y a %d joysticks.\n",SDL_NumJoysticks()); // on écrit combien il y a de joysticks
//    for(i=0;i<SDL_NumJoysticks();i++)
//        printf("Nom du joystick numero %d : %s\n",i,SDL_JoystickName(i)); // on écrit les noms des joysticks
//
//    printf("Nombre de boutons : %d\n",SDL_JoystickNumButtons(joystick)); // nombre de boutons
//    printf("Nombre d'axes : %d\n",SDL_JoystickNumAxes(in.joystick)); // nombre d'axes
//    printf("Nombre de chapeaux : %d\n",SDL_JoystickNumHats(joystick)); // nombre de chapeaux
//    printf("Nombre de trackballs : %d\n",SDL_JoystickNumBalls(joystick)); // nombre de trackballs*/
//    while(1)
//    {
//        SDL_JoystickUpdate();
//        printf("%d\n",SDL_JoystickGetAxis(in.joystick,1));
//    }

    while (go) //main loop
    {

        if(titleMenu(screen,&go,sound_system,&in))
        {
            while((ret1 = mainMenu(screen,&go,sound_system,&in)) != -1)
                switch(ret1)
                {
                    case -1:
                        break;
                    case 0:
                        if (menuLevel(screen,level_name,sound_system,&go,&in))
                            while(play(screen,level_name,sound_system,&go,kc,&in));
                        break;
                    case 1:
                        while((ret = optionMenu(screen,&go,sound_system,kc,&in)) != -1)
                            switch(ret)
                            {
                                case -1:
                                    break;
                                case 0:
                                    soundOptions(screen,&go,sound_system,&in);
                                    break;
                                case 1:
                                    keyBoardOptions(screen,&go,kc,&in);
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

    freeInput(&in);
    SDL_Quit();

    return EXIT_SUCCESS;
}
