/**
 *\file menu_option.c
 *\brief containe the option menu functions
 *\author X.COPONET
 *\date 2014-04-27
*/

#include "menu_option.h"

/**
 *\fn int optionMenu(SDL_Surface *screen,int *go,Sound *sound_sys,keyConf *kc)
 *print the option menu on the screen
 *\param[out] screen the game screen
 *\param[in,out] go main loop validation
 *\param[in,out] sys sound system
 *\param[in,out] kc the keyboard configuration structure
 *\return the number of the option which is choosen, -1 if esc
 */
int optionMenu(SDL_Surface *screen,int *go,Sound *sound_sys,keyConf *kc)
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int nb_option = 1;
    char option_names[1][MAX_SIZE_FILE_NAME]={"Sound"};
    int i,ret = 1;
    int text_size;
    int pos_curseur=0;


    Input in;

    SDL_Rect posText={0,0,0,0};

    /*winting screen */
    waiting = imageLoadAlpha("sprites/Background/desert_hills_2.png");
    posWait.x = 0;
    posWait.y = 0;

    memset(&in,0,sizeof(in));

    while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN])
    {
        updateWaitEvents(&in,go);
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
                printText(screen,&posText,option_names[i],0,0,0,"polices/ubuntu.ttf",text_size,1);
            else
            {
                printText(screen,&posText,option_names[i],255,60,30,"polices/ubuntu.ttf",text_size,1);
            }
        }

        SDL_Flip(screen);

    }

    SDL_FreeSurface(waiting);
    if(!ret)
    {
        saveOptions(".conf",sound_sys,kc);
        return -1;
    }

    return pos_curseur;
}

/**
 *\fn void soundOptions(SDL_Surface *screen,int *go,Sound *sound_sys)
 *print the sound options and deals with the user choises
 *\param[out] screen the game screen
 *\param[in,out] go main loop validation
 *\param[out] sys sound system
 */
void soundOptions(SDL_Surface *screen,int *go,Sound *sound_sys)
{
    SDL_Surface *waiting;
    SDL_Rect posWait,value;
    int nb_option = 2;
    char option_names[2][MAX_SIZE_FILE_NAME]={"Effects :","Music :"};
    int i;
    int text_size;
    int pos_curseur=0;
    float curVol;

    Input in;

    SDL_Rect posText={0,0,0,0};

    /*winting screen */
    waiting = imageLoadAlpha("sprites/Background/desert_hills_2.png");
    posWait.x = 0;
    posWait.y = 0;

    memset(&in,0,sizeof(in));

    while(!in.key[SDLK_ESCAPE] && !in.quit)
    {
        updateWaitEvents(&in,go);
        keyboardActionMenu(&in,&pos_curseur,NULL,nb_option);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        for (i=0 ; i < nb_option ; i++)
        {
            posText.x = 70;
            text_size=screen->h / nb_option;
            if (text_size > 60)
                text_size=60;
            value.y = posText.y = screen->h / (1+nb_option) * (i+1) - text_size/2;
            value.x = 300;
            value.h = text_size;
            switch(i)
            {
                case 0:
                    value.w = 500*sound_sys->fxVolume;
                    break;
                case 1:
                    value.w = 500*sound_sys->musicVolume;
                    break;
                default:;
            }

            if(i != pos_curseur)
                printText(screen,&posText,option_names[i],0,0,0,"polices/ubuntu.ttf",text_size,1);
            else
                printText(screen,&posText,option_names[i],255,60,30,"polices/ubuntu.ttf",text_size,1);

            SDL_FillRect(screen,&value,SDL_MapRGB(screen->format,200,0,0));
        }

        SDL_Flip(screen);

        switch(pos_curseur)
        {
            case 0:
                curVol = sound_sys->fxVolume;
                if(in.key[SDLK_RIGHT] && !in.key[SDLK_LEFT])
                    curVol += 0.1;
                if(!in.key[SDLK_RIGHT] && in.key[SDLK_LEFT])
                    curVol -= 0.1;
                if(curVol < 0)
                    curVol = 0;
                if(curVol > 1)
                    curVol = 1;
                soundVolume(sound_sys,0,curVol);
                break;
            case 1:
                curVol = sound_sys->musicVolume;
                if(in.key[SDLK_RIGHT] && !in.key[SDLK_LEFT])
                    curVol += 0.1;
                if(!in.key[SDLK_RIGHT] && in.key[SDLK_LEFT])
                    curVol -= 0.1;
                if(curVol < 0)
                    curVol = 0;
                if(curVol > 1)
                    curVol = 1;
                soundVolume(sound_sys,1,curVol);
                break;
            default:;
        }
    }

    SDL_FreeSurface(waiting);
}
