/*!
 * \file sound.c
 * \brief contient les fonction pour jouer du son
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#include "sound.h"

/**
 *\fn sound *createSound(void)
 *create a sound structure
 *\return the sound structure
 */
 Sound *createSound(void)
 {
    Sound *s = NULL;
    s = (Sound *)malloc(sizeof(Sound));
    if(s == NULL)
    {
        perror("allocation error");
        exit(errno);
    }

    FMOD_System_Create(&s->sys);
    FMOD_System_Init(s->sys, 32, FMOD_INIT_NORMAL, NULL);


    FMOD_System_GetChannel(s->sys,0,&s->fx);
    FMOD_System_GetChannel(s->sys,1,&s->music);
    s->fxVolume = 1;
    s->musicVolume=1;

    return s;
 }

/**
 *\fn void playMusic(char *file,Sound *s)
 *play a long sound file (music)
 *\param[in] file the sound file to be played
 *\param[out] s the sound system we manipulate
 */
void playMusic(char *file,Sound *s)
{
    FMOD_SOUND *sound;
    /*chargement du fichier son*/
    if(FMOD_System_CreateSound(s->sys, file,
                FMOD_LOOP_NORMAL|FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM,
                0, &sound) != FMOD_OK)
    {
        perror("can't read audio file");
        exit(errno);
    }

    /* On active la répétition de la musique à l'infini */
    FMOD_Sound_SetLoopCount(sound, -1);


    /* On joue la musique */
    FMOD_System_PlaySound(s->sys,1, sound,0, NULL);
    FMOD_Channel_SetVolume(s->music,s->musicVolume);
}

/**
 *\fn void playShortSound(char *file,Sound *s)
 *play a short sound file (effect sound)
 *\param[in] file the sound file to be played
 *\param[out] s the sound system we manipulate
 */
void playShortSound(char *file,Sound *s)
{
    FMOD_SOUND *sound;
    /*chargement du fichier son*/
    if(FMOD_System_CreateSound(s->sys, file,
                FMOD_CREATESAMPLE,
                0, &sound) != FMOD_OK)
    {
        perror("can't read audio file");
        exit(errno);
    }

    /* On joue le son */
    FMOD_System_PlaySound(s->sys,0,sound,0,NULL);
    FMOD_Channel_SetVolume(s->fx,s->fxVolume);
}


/**
 *\fn void freeSound(Sound *s)
 *release the sound
 *\param[out] s the sound
 */
void freeSound(Sound *s)
{
    FMOD_System_Close(s->sys);
    FMOD_System_Release(s->sys);

    free((void *)s);
}



/**
 *\fn void stopSound(Sound *s,int chan)
 *stop the sound
 *\param[out] s the sound system
 *\param[in] chan the channel which has to be stoped
 */
void stopSound(Sound *s,int chan)
{
    switch(chan)
    {
        case 0:
            FMOD_Channel_Stop(s->fx);
            break;
        case 1:
            FMOD_Channel_Stop(s->music);
            break;
        default: ;
    }
}

/**
 *\fn void soundVolume(Sound *s,int chan,float volume)
 *set the sound volume
 *\param[out] s the sound system
 *\param[in] chan the channel which the volume's has to be changed
 *\param[in] volume the sound volume : [0.0 : no sound ; 1.0 (default) max power]
 */
void soundVolume(Sound *s,int chan,float volume)
{
    switch(chan)
    {
        case 0:
            s->fxVolume = volume;
            break;
        case 1:
            s->musicVolume = volume;
            break;
        default: ;
    }

}
