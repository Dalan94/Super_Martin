/*!
 * \file sound.c
 * \brief contains the sound playing function
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#include "sound.h"


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

    s->mscSound = NULL;
    s->fxSound = NULL;

    FMOD_System_GetChannel(s->sys,0,&s->fx);
    FMOD_System_GetChannel(s->sys,1,&s->music);
    s->fxVolume = 1;
    s->musicVolume=1;

    return s;
 }


void playMusic(char *file,Sound *s)
{
    FMOD_BOOL b;
    int index;

    FMOD_Channel_IsPlaying(s->music,&b);

    if(!b)
    {

        if(FMOD_System_CreateSound(s->sys, file,
                    FMOD_LOOP_NORMAL|FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM,
                    0, &s->mscSound) != FMOD_OK)
        {
            perror("can't read audio file");
            exit(errno);
        }

        /* infinite repetition */
        FMOD_Sound_SetLoopCount(s->mscSound, -1);


        /* playing the music */
        FMOD_Channel_GetIndex(s->music,&index);
        FMOD_System_PlaySound(s->sys,index, s->mscSound,0, NULL);
        FMOD_Channel_SetVolume(s->music,s->musicVolume);


    }
}


void playShortSound(char *file,Sound *s)
{
    if(s == NULL)
        return;
    /*sound file loading*/
    if(FMOD_System_CreateSound(s->sys, file,
                FMOD_CREATESAMPLE,
                0, &s->fxSound) != FMOD_OK)
    {
        perror("can't read audio file");
        exit(errno);
    }

    /* sound playing */
    FMOD_System_PlaySound(s->sys,0,s->fxSound,0,NULL);
    FMOD_Channel_SetVolume(s->fx,s->fxVolume);
}



void freeSound(Sound *s)
{
    FMOD_System_Close(s->sys);
    FMOD_System_Release(s->sys);

    free((void *)s);
}




void stopSound(Sound *s,int chan)
{
    switch(chan)
    {
        case 0:
            FMOD_Channel_Stop(s->fx);
            FMOD_Sound_Release(s->fxSound);
            break;
        case 1:
            FMOD_Channel_Stop(s->music);
            FMOD_Sound_Release(s->mscSound);
            break;
        default: ;
    }
}


void soundVolume(Sound *s,int chan,float volume)
{
    switch(chan)
    {
        case 0:
            s->fxVolume = volume;
            FMOD_Channel_SetVolume(s->fx,volume);
            break;
        case 1:
            s->musicVolume = volume;
            FMOD_Channel_SetVolume(s->music,volume);
            break;
        default: ;
    }

}
