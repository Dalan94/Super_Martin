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

void loadOptions(char confFile[],Sound *soundSys,SDLKey *kc);
void saveOptions(char confFile[],Sound *soundSys,SDLKey *kc);

void chooseKey(SDL_Surface *screen,Input *in,char *action,SDLKey *kc,int nb);

#endif // OPTION_H_INCLUDED
