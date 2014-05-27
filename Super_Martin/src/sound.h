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
    FMOD_SOUND *mscSound;
    FMOD_SOUND *fxSound;
    float musicVolume; /*! the music volume */
    float fxVolume; /*! the effect volume */
}Sound;

/*prototypes*/
/**
 *\fn sound *createSound(void)
 *create a sound structure
 *\return the sound structure
 */
Sound *createSound(void);

/**
 *\fn void playMusic(char *file,Sound *s)
 *play a long sound file (music)
 *\param[in] file the sound file to be played
 *\param[out] s the sound system we manipulate
 */
void playMusic(char *file,Sound *s);

/**
 *\fn void playShortSound(char *file,Sound *s)
 *play a short sound file (effect sound)
 *\param[in] file the sound file to be played
 *\param[out] s the sound system we manipulate
 */
void playShortSound(char *file,Sound *s);

/**
 *\fn void freeSound(Sound *s)
 *release the sound
 *\param[out] s the sound
 */
void freeSound(Sound *s);

/**
 *\fn void stopSound(Sound *s,int chan)
 *stop the sound
 *\param[out] s the sound system
 *\param[in] chan the channel which has to be stoped
 */
void stopSound(Sound *s,int chan);

/**
 *\fn void soundVolume(Sound *s,int chan,float volume)
 *set the sound volume
 *\param[out] s the sound system
 *\param[in] chan the channel which the volume's has to be changed
 *\param[in] volume the sound volume : [0.0 : no sound ; 1.0 (default) max power]
 */
void soundVolume(Sound *s,int chan,float volume);


#endif // SOUND_H
