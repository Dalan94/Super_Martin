/**
 *\file menu_option.c
 *\brief contains the option menu functions
 *\author X.COPONET
 *\date 2014-04-27
*/

#include "menu_option.h"


int optionMenu(SDL_Surface *screen,int *go,Sound *sound_sys,SDLKey *kc,Input *in)
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int nb_option = 2;
    char option_names[2][MAX_SIZE_FILE_NAME]={"Sound","Keyboard"};
    int i,ret = 1;
    int text_size;
    int pos_curseur=0;


    SDL_Rect posText={0,0,0,0};


    /*winting screen */
    waiting = imageLoadAlpha("sprites/Background/menu_background.png");
    posWait.x = 0;
    posWait.y = 0;

    memset(&in->key,0,SDLK_LAST*sizeof(char));
    if(in->isJoystick)
        initInput(in);

    while(!in->key[SDLK_ESCAPE] && !in->quit && !in->key[SDLK_RETURN]
           && (!in->isJoystick||!(in->button[A] || in->button[BACK])))
    {
        updateWaitEvents(in,go);
        inputActionMenu(in,&pos_curseur,&ret,nb_option);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        for (i=0 ; i < nb_option ; i++)
        {
            posText.x = -1;
            text_size=screen->h / nb_option;
            if (text_size > 30)
                text_size=30;
            posText.y = 150 + (screen->h - 350)/ (1+nb_option) * (i+1) - text_size/2;
            if(i != pos_curseur)
                printText(screen,&posText,option_names[i],0,0,0,"polices/PressStart2P.ttf",text_size,1);
            else
            {
                printText(screen,&posText,option_names[i],255,60,30,"polices/PressStart2P.ttf",text_size,1);
            }
        }

        SDL_Flip(screen);

    }

    SDL_FreeSurface(waiting);
    if(!ret)
        return -1;

    return pos_curseur;
}


void soundOptions(SDL_Surface *screen,int *go,Sound *sound_sys, Input *in)
{
    SDL_Surface *waiting;
    SDL_Rect posWait,value;
    int nb_option = 2;
    char option_names[2][MAX_SIZE_FILE_NAME]={"Effects :","Music :"};
    int i;
    int text_size;
    int pos_curseur=0;
    float curVol;


    SDL_Rect posText={0,0,0,0};

    /*winting screen */
    waiting = imageLoadAlpha("sprites/Background/menu_background.png");
    posWait.x = 0;
    posWait.y = 0;

    memset(&in->key,0,SDLK_LAST*sizeof(char));
    if(in->isJoystick)
        initInput(in);

    while(!in->key[SDLK_ESCAPE] && !in->quit && (!in->isJoystick||!in->button[BACK]))
    {
        updateWaitEvents(in,go);
        inputActionMenu(in,&pos_curseur,NULL,nb_option);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        for (i=0 ; i < nb_option ; i++)
        {
            posText.x = 300;
            text_size=screen->h / nb_option;
            if (text_size > 30)
                text_size=30;
            value.y = posText.y = 150 + (screen->h - 300) / (1+nb_option) * (i+1) - text_size/2;
            value.x = 570;
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
                printText(screen,&posText,option_names[i],0,0,0,"polices/PressStart2P.ttf",text_size,1);
            else
                printText(screen,&posText,option_names[i],255,60,30,"polices/PressStart2P.ttf",text_size,1);

            SDL_FillRect(screen,&value,SDL_MapRGB(screen->format,200,0,0));
        }

        SDL_Flip(screen);

        switch(pos_curseur)
        {
            case 0:
                curVol = sound_sys->fxVolume;
                if((in->key[SDLK_RIGHT] && !in->key[SDLK_LEFT]) || (in->isJoystick&&(in->hat[0] == SDL_HAT_RIGHT)))
                    curVol += 0.1;
                if((!in->key[SDLK_RIGHT] && in->key[SDLK_LEFT]) || (in->isJoystick&&(in->hat[0] == SDL_HAT_LEFT)))
                    curVol -= 0.1;
                if(curVol < 0)
                    curVol = 0;
                if(curVol > 1)
                    curVol = 1;
                soundVolume(sound_sys,0,curVol);
                break;
            case 1:
                curVol = sound_sys->musicVolume;
                if((in->key[SDLK_RIGHT] && !in->key[SDLK_LEFT]) || (in->isJoystick&&(in->hat[0] == SDL_HAT_RIGHT)))
                    curVol += 0.1;
                if((!in->key[SDLK_RIGHT] && in->key[SDLK_LEFT]) || (in->isJoystick&&(in->hat[0] == SDL_HAT_LEFT)))
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

    saveSoundOptions("configuration/sound.conf",sound_sys);


    SDL_FreeSurface(waiting);
}


void keyBoardOptions(SDL_Surface *screen,int *go,SDLKey *kc,Input *in,char *player_name)
{
    SDL_Surface *waiting;
    SDL_Rect posWait;
    int nb_key = NB_KEY;
    char key_names[NB_KEY][MAX_SIZE_FILE_NAME]={"Left","Right","Jump","Pause","Hammer","Joystick"};
    int i,j;
    int text_size;
    int pos_curseur=0;
    char key[MAX_SIZE_FILE_NAME],st[MAX_SIZE_FILE_NAME];


    SDL_Rect posText={0,0,0,0};

    /*winting screen */
    waiting = imageLoadAlpha("sprites/Background/menu_background.png");
    posWait.x = 0;
    posWait.y = 0;

    memset(&in->key,0,SDLK_LAST*sizeof(char));
    if(in->isJoystick)
        initInput(in);

    while(!in->key[SDLK_ESCAPE] && !in->quit && (!in->isJoystick||!in->button[BACK]))
    {
        updateWaitEvents(in,go);
        inputActionMenu(in,&pos_curseur,NULL,nb_key);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));

        SDL_BlitSurface(waiting, NULL, screen, &posWait);

        for (i=0 ; i < nb_key ; i++)
        {
            posText.x = 70;
            text_size=screen->h / nb_key;
            if (text_size > 30)
                text_size=30;
            posText.y = 150 + (screen->h -350)/ (1+nb_key) * (i+1) - text_size/2;
            posText.x = -1;

            sprintf(st,"%s",SDL_GetKeyName(kc[i]));

            /* joystick gestion*/
            if(i == NB_KEY-1 && in->useJoystick)
            {
                sprintf(st,"on");
            }
            if(i == NB_KEY-1 && !in->useJoystick)
            {
                sprintf(st,"off");
            }

            /* Key name in capital letter */
            for(j=0;j<strlen(st);j++)
            {
                st[j]-=32;
                if(st[j]<0)
                    st[j]=0;
            }

                /* print the row on the screen*/
            sprintf(key,"%s : %s",key_names[i],st);
            if(i != pos_curseur)
            {
                if(i == NB_KEY-1 && !in->isJoystick)
                    printText(screen,&posText,key,117,117,117,"polices/PressStart2P.ttf",text_size,1);
                else
                    printText(screen,&posText,key,0,0,0,"polices/PressStart2P.ttf",text_size,1);
            }
            else
                printText(screen,&posText,key,255,60,30,"polices/PressStart2P.ttf",text_size,1);
                /* ******* */
        }

        SDL_Flip(screen);

        if(in->key[SDLK_RETURN] || (in->isJoystick&&in->button[A]))
        {
            if(pos_curseur != NB_KEY-1)
                chooseKey(screen,in,key_names[pos_curseur],kc,pos_curseur); //choisir la touche
            else
                if(in->isJoystick)
                    in->useJoystick ^= 1; // si joystick, toggle l'indicatrice d'utilisation du joystick
        }
    }

    SDL_FreeSurface(waiting);
    saveInputOptions(player_name,kc,in);
}



void chooseKey(SDL_Surface *screen,Input *in,char *action,SDLKey *kc,int nb)
{

    int i = 0,j;
    SDL_Surface *keyChoose = NULL;
    SDL_Rect posGame;
    char st[MAX_SIZE_FILE_NAME];

    keyChoose = imageLoad("sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(keyChoose, SDL_SRCALPHA, 200);
    SDL_BlitSurface(keyChoose,NULL,screen,&posGame);

    sprintf(st,"Please, choose a key for %s",action);
    printText(screen,NULL,st,186,38,18,"polices/PressStart2P.ttf",30,1);
    SDL_Flip(screen);

    SDL_Delay(1500);

    memset(&in->key,0,sizeof(char)*SDLK_LAST);

    while(!updateWaitEvents(in,NULL));
    for(i=SDLK_SPACE;i<SDLK_LAST;i++)
    {
        if(in->key[i])
        {
            for (j=0;j<NB_KEY;j++)
                if(kc[j] == i)
                {
                    kc[j] = SDLK_UNKNOWN;
                    break;
                }
            kc[nb] = i;
            break;
        }
    }
    SDL_FreeSurface(keyChoose);
}
