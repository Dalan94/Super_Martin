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


/**
 *\struct Sound
 * the sound gestion structure
 */
typedef struct
{
    FMOD_SYSTEM *sys; /*! the sound system*/
    FMOD_CHANNEL *music; /*! the music channel*/
    FMOD_CHANNEL *fx; /*! the effects channel */
    float musicVolume; /*! the music volume */
    float fxVolume; /*! the effect volume */
}Sound;

/*prototypes*/
Sound *createSound(void);
void playMusic(char *file,Sound *s);
void playMusicOnce(Sound *s, char *file);
void freeSound(Sound *s);
void stopSound(Sound *s,int chan);
void soundVolume(Sound *s,int chan,float volume);


#endif // SOUND_H
