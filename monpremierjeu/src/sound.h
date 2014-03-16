/*!
 * \file sound.h
 * \brief header de sound.c
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#ifndef SOUND_H
#define SOUND_H

#include <FMOD/fmod.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

typedef struct {
    FMOD_SYSTEM *sys;
    FMOD_SOUND *sound;
    FMOD_CHANNELGROUP *channel;
}Sound;

/*prototypes*/
Sound *createSound(void);
void playMusic(Sound *s, char *file);
void freeSound(Sound *s);
void stopSound(Sound *s);

#endif // SOUND_H
