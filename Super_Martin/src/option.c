/**
 *\file option.c
 *\brief contains the funtions that manipulate the options
 *\author X.COPONET
 *\date 2014-04-28
*/

#include "option.h"


void loadSoundOptions(char confFile[],Sound *soundSys)
{
    FILE *fl;
    fl = openFile(confFile,"rb");
    if(fl == NULL)
    {
        perror("error while opening the config file");
        exit(errno);
    }

    fread(&soundSys->fxVolume,sizeof(float),1,fl);
    fread(&soundSys->musicVolume,sizeof(float),1,fl);

    closeFile(fl);
}


void saveSoundOptions(char confFile[],Sound *soundSys)
{
    FILE *fl;
    fl = openFile(confFile,"wb");
    if(fl == NULL)
    {
        perror("error while opening the config file");
        exit(errno);
    }
    fwrite(&soundSys->fxVolume,sizeof(float),1,fl);
    fwrite(&soundSys->musicVolume,sizeof(float),1,fl);
//    fwrite(kc,sizeof(SDLKey),NB_KEY-1,fl);
//    fwrite(&in->useJoystick,sizeof(int),1,fl);

    closeFile(fl);
}


void loadInputOptions(char player_name[],SDLKey *kc,Input *in)
{
    char confFile[MAX_SIZE_FILE_NAME];
    FILE *fl;

    sprintf(confFile,"configuration/%s.conf",player_name);
    fl = openFile(confFile,"rb");
    if(fl == NULL)
    {
        perror("error while opening the config file");
        return ;
    }
    fread(kc,sizeof(SDLKey),NB_KEY-1,fl);
    fread(&in->useJoystick,sizeof(int),1,fl);

    closeFile(fl);
}


void saveInputOptions(char player_name[],SDLKey *kc, Input *in)
{
    FILE *fl;
    char confFile[MAX_SIZE_FILE_NAME];

    sprintf(confFile,"configuration/%s.conf",player_name);
    fl = openFile(confFile,"wb");
    if(fl == NULL)
    {
        perror("error while opening the config file");
        exit(errno);
    }
    fwrite(kc,sizeof(SDLKey),NB_KEY-1,fl);
    fwrite(&in->useJoystick,sizeof(int),1,fl);

    closeFile(fl);
}
