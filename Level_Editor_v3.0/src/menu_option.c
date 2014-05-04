/**
 *\file menu_option.c
 *\brief containe the option menu functions
 *\author X.COPONET
 *\date 2014-04-27
*/

#include "menu_option.h"

/**
 *\fn int menuOptions(SDL_Surface *screen,int *go,Sound *sound_sys,keyConf *kc)
 *print the option menu on the screen
 *\param[out] screen the game screen
 *\param[in,out] go main loop validation
 *\param[in,out] sys sound system
 *\param[in,out] kc the keyboard configuration structure
 *\return the number of the option which is choosen, -1 if esc
 */
int menuOptions(SDL_Surface *screen,int *go,SDLKey *kc)
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int nb_option = 1;
    char option_names[1][MAX_LENGTH_FILE_NAME]={"Keyboard"};
    int i,ret = 1;
    int text_size;
    int pos_curseur=0;


    Input in;

    SDL_Rect posText={0,0,0,0};


    /*winting screen */
    waiting = imageLoadAlpha("../Super_Martin/sprites/Background/menu_background.png");
    posWait.x = 0;
    posWait.y = 0;

    memset(&in,0,sizeof(in));

    while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN])
    {
        updateWaitEvents(&in);
        keyboardActionMenu(&in,&pos_curseur,&ret,nb_option);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        for (i=0 ; i < nb_option ; i++)
        {
            posText.x = 150;
            text_size=screen->h / nb_option;
            if (text_size > 60)
                text_size=60;
            posText.y = screen->h / (1+nb_option) * (i+1) - text_size/2;
            if(i != pos_curseur)
                printText(screen,&posText,option_names[i],0,0,0,"../Super_Martin/polices/ubuntu.ttf",text_size,1);
            else
            {
                printText(screen,&posText,option_names[i],255,60,30,"../Super_Martin/polices/ubuntu.ttf",text_size,1);
            }
        }

        SDL_Flip(screen);

    }

    SDL_FreeSurface(waiting);


    return pos_curseur;
}


/**
 *\fn void keyboardOptions(SDL_Surface *screen,int *go,SDLKey *kc)
 *print the keyboard options and deals with the user choises
 *\param[out] screen the game screen
 *\param[in,out] go main loop validation
 *\param[in,out] kc the keyboard config structure
 */
void keyBoardOptions(SDL_Surface *screen,int *go,SDLKey *kc)
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int nb_key = 15;
    char key_names[15][MAX_LENGTH_FILE_NAME]={"Left","Right","Save","Reset", "Enemy", "Tree", "Flower", "Cloud", "Ground", "Coin", "Rock", "Spring", "Blank", "Platform", "Help"};
    int i, ret =1;
    int text_size;
    int pos_curseur=0;
    char key[MAX_LENGTH_FILE_NAME];


    Input in;

    SDL_Rect posText={0,0,0,0};

    /*winting screen */
    waiting = imageLoadAlpha("../Super_Martin/sprites/Background/menu_background.png");
    posWait.x = 0;
    posWait.y = 0;

    memset(&in,0,sizeof(in));

    while(!in.key[SDLK_ESCAPE] && !in.quit)
    {
        updateWaitEvents(&in);
        keyboardActionMenu(&in,&pos_curseur,&ret,nb_key);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        for (i=0 ; i < nb_key ; i++)
        {

            text_size= (screen->h -300)/ (min(nb_key, OPTIONS_PER_COLUMN));
            if (text_size > 35)
                text_size=35;
            if(i>=OPTIONS_PER_COLUMN)
            {
                posText.x = 680;
                posText.y = 150 +screen->h / (1.5*(1+OPTIONS_PER_COLUMN)) * (i+1-OPTIONS_PER_COLUMN) - text_size;
            }
            else
            {
                posText.x = 300;
                posText.y = 150 + screen->h / (1.5*(1+min(OPTIONS_PER_COLUMN, nb_key))) * (i+1) - text_size;
            }



            sprintf(key,"%s : %s",key_names[i],SDL_GetKeyName(kc[i]));

            if(i != pos_curseur)
                printText(screen,&posText,key,0,0,0,"../Super_Martin/polices/ubuntu.ttf",text_size,1);
            else
                printText(screen,&posText,key,255,60,30,"../Super_Martin/polices/ubuntu.ttf",text_size,1);
        }

        SDL_Flip(screen);

        if(in.key[SDLK_RETURN])
        {
            chooseKey(screen,&in,key_names[pos_curseur],kc,pos_curseur);
        }
    }
    if(!ret)
    {
        saveOptions(".conf",kc);
    }
    SDL_FreeSurface(waiting);
}

/**
 *\fn void chooseKey(SDL_Surface *screen,Input *in,char *action,SDLKey *kc,int nb)
 *print the message asking the player to choose a key and wait until the player press a key and deals with this key
 *\param[out] screen the game screen
 *\param[in,out] in the input structure
 *\param[in] action the action which the key has to be choosen
 *\param[out] kc the keyboard configuration
 *\param[in] nb the number of the action
 */

void chooseKey(SDL_Surface *screen,Input *in,char *action,SDLKey *kc,int nb)
{

    int i = 0;
    SDL_Surface *keyChoose = NULL;
    SDL_Rect posGame;
    char st[MAX_LENGTH_FILE_NAME];

    keyChoose = imageLoad("../Super_Martin/sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(keyChoose, SDL_SRCALPHA, 200);
    SDL_BlitSurface(keyChoose,NULL,screen,&posGame);

    sprintf(st,"Please, choose a key for %s",action);
    printText(screen,NULL,st,186,38,18,"polices/ubuntu.ttf",65,1);
    SDL_Flip(screen);

    SDL_Delay(1500);

    memset(in,0,sizeof(in));

    while(!updateWaitEvents(in));
    for(;i<SDLK_LAST;i++)
    {
        if(in->key[i])
        {
            kc[nb] = i;
            break;
        }
    }
    SDL_FreeSurface(keyChoose);
}
