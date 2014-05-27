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

/**
 *\fn void loadSoundOptions(char confFile[],Sound *soundSys)
 *load the sound options from the sound config file
 *\param[in] confFile the config file path
 *\param[out] soundSys the sound system
 */
void loadSoundOptions(char confFile[],Sound *soundSys);

/**
 *\fn void saveSoundOptions(char confFile[],Sound *soundSys)
 *save the sound options to the config file
 *\param[in] confFile the config file path
 *\param[in] soundSys the sound system
 */
void saveSoundOptions(char confFile[],Sound *soundSys);

/**
 *\fn void loadInputOptions(char player_name[],SDLKey *kc,Input *in)
 *load the input options from the player input config file
 *\param[in] player_name the current player's name
 *\param[out] kc the keyboard configuration structure
 *\param[out] in the input structure
 */
void loadInputOptions(char player_name[],SDLKey *kc,Input *in);

/**
 *\fn void saveInputOptions(char player_name[],SDLKey *kc, Input *in)
 *save the input options to the player input config file
 *\param[in] player_name the current player name
 *\param[out] kc the keyboard configuration structure
 *\param[out] in the input structure
 */
void saveInputOptions(char player_name[],SDLKey *kc, Input *in);


#endif // OPTION_H_INCLUDED
