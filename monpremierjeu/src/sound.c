/*!
 * \file sound.c
 * \brief contient les fonction pour jouer du son
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#include "sound.h"

/**
 *\fn sound *createSound(void)
 *créer une structure son
 *\return la structure son
 */
 Sound *createSound(void){
    Sound *s;
    s = (Sound *)malloc(sizeof(Sound));
    if(s == NULL){
        perror("allocation error");
        exit(errno);
    }

    FMOD_System_Create(&(s->sys));
    FMOD_System_Init(s->sys, 2, FMOD_INIT_NORMAL, NULL);
    s->sound = NULL;
    s->channel = NULL;

    return s;
 }

/**
 *\fn void playMusic(Sound *s, char *file)
 *lit un fichier long (musique)
 *\param[in,out] s la structure son que l'on manipule
 *\param[in] file Le fichier son à lire
 */
void playMusic(Sound *s, char *file){

    /*chargement du fichier son*/
    if(FMOD_System_CreateSound(s->sys, file,
                FMOD_LOOP_NORMAL|FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM,
                0, &(s->sound)) != FMOD_OK){
        perror("can't read audio file");
        exit(errno);
    }

    /* On active la répétition de la musique à l'infini */
    FMOD_Sound_SetLoopCount(s->sound, -1);

    /* On joue la musique */
    FMOD_System_PlaySound(s->sys, FMOD_CHANNEL_FREE, s->sound, 0, NULL);

}

void freeSound(Sound *s){
    FMOD_Sound_Release(s->sound);
    FMOD_System_Close(s->sys);
    FMOD_System_Release(s->sys);

    free((void *)s);
}
