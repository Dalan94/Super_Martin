/**
 *\file option.c
 *\brief contains the funtions that manipulate the options
 *\author X.COPONET
 *\date 2014-04-28
*/

#include "option.h"

/**
 *\fn void loadOptions(char confFile[],Sound *soundSys,keyConf *kc)
 *load the options from the config file
 *\param[in] confFile the config file path
 *\param[out] soundSys the sound system
 *\param[out] kc the keyboard configuration structure
 */
void loadOptions(char confFile[],SDLKey *kc)
{
    FILE *fl;
    fl = openFile(confFile,"rb");
    if(fl == NULL)
    {
        perror("error while opening the config file");
        exit(errno);
    }

    //fread(&soundSys->fxVolume,sizeof(float),1,fl);
    //fread(&soundSys->musicVolume,sizeof(float),1,fl);
    fread(kc,sizeof(SDLKey),15,fl);

    closeFile(fl);
}

/**
 *\fn void saveOptions(char confFile[],Sound *soundSys,keyConf *kc)
 *save the options to the config file
 *\param[in] confFile the config file path
 *\param[in] soundSys the sound system
 *\param[in] kc the keyboard configuration structure
 */
void saveOptions(char confFile[],SDLKey *kc)
{
    FILE *fl;
    fl = openFile(confFile,"wb");
    if(fl == NULL)
    {
        perror("error while opening the config file");
        exit(errno);
    }
    //fwrite(&soundSys->fxVolume,sizeof(float),1,fl);
    //fwrite(&soundSys->musicVolume,sizeof(float),1,fl);
    fwrite(kc,sizeof(SDLKey),15,fl);

    closeFile(fl);
}
