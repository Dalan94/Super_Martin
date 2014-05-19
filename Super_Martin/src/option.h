/*!
 * \file option.h
 * \brief option.c header
 * \author Xavier COPONET
 * \date 2014-04-28
 */

#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED

#include "file.h"
#include "sound.h"
#include "structures.h"
#include "input.h"

void loadSoundOptions(char confFile[],Sound *soundSys);
void saveSoundOptions(char confFile[],Sound *soundSys);

void loadInputOptions(char player_name[],SDLKey *kc,Input *in);
void saveInputOptions(char player_name[],SDLKey *kc, Input *in);


#endif // OPTION_H_INCLUDED
