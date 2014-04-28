/**
 *\file option.c
 *\brief contains the funtions that manipulate the options
 *\author X.COPONET
 *\date 2014-04-28
*/

#include "option.h"

/**
 *\fn void loadOptions(char confFile[],Sound *soundSys)
 *load the options from the config file
 *\param[in] confFile the config file path
 *\param[out] soundSys the sound system
 */
void loadOptions(char confFile[],Sound *soundSys)
{
    FILE *fl;
    fl = openFile(confFile,"r");
    if(fl == NULL)
    {
        perror("error while opening the config file");
        exit(errno);
    }

    fscanf(fl,"%f",&soundSys->fxVolume);
    fscanf(fl,"%f",&soundSys->musicVolume);

    closeFile(fl);
}

/**
 *\fn void saveOptions(char confFile[],Sound *soundSys)
 *save the options to the config file
 *\param[in] confFile the config file path
 *\param[out] soundSys the sound system
 */
void saveOptions(char confFile[],Sound *soundSys)
{
    FILE *fl;
    fl = openFile(confFile,"w");
    if(fl == NULL)
    {
        perror("error while opening the config file");
        exit(errno);
    }
    fprintf(fl,"%f\n",soundSys->fxVolume);
    fprintf(fl,"%f\n",soundSys->musicVolume);

    closeFile(fl);
}
