/**
 *\file option.c
 *\brief contains the functions that manipulate the options
 *\author Xavier COPONET, Glenn HERROU
 *\date 2014-04-28
*/

#include "option.h"

void loadOptions(char confFile[],SDLKey *kc)
{
    FILE *fl;
    fl = openFile(confFile,"rb");
    if(fl == NULL)
    {
        perror("error while opening the config file");
        exit(errno);
    }

    fread(kc,sizeof(SDLKey),18,fl);

    closeFile(fl);
}

void saveOptions(char confFile[],SDLKey *kc)
{
    FILE *fl;
    fl = openFile(confFile,"wb");
    if(fl == NULL)
    {
        perror("error while opening the config file");
        exit(errno);
    }

    fwrite(kc,sizeof(SDLKey),18,fl);

    closeFile(fl);
}
