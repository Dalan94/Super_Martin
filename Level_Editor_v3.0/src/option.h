/*!
 * \file option.h
 * \brief option.c header
 * \author Xavier COPONET
 * \date 2014-04-28
 */

#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED

#include "file.h"
#include "structures.h"
#include "input.h"

/**
 *\fn void loadOptions(char confFile[],Sound *soundSys,keyConf *kc)
 *Load the options from the config file
 *\param[in] confFile the config file path
 *\param[out] kc the keyboard configuration structure
 */

void loadOptions(char confFile[],SDLKey *kc);

/**
 *\fn void saveOptions(char confFile[],keyConf *kc)
 *save the options to the config file
 *\param[in] confFile the config file path
 *\param[in] kc the keyboard configuration structure
 */

void saveOptions(char confFile[],SDLKey *kc);

#endif // OPTION_H_INCLUDED
