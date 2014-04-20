/*!
 * \file image.c
 * \brief contient les fonction liées aux images
 * \author Rémi BERTHO
 * \date 2014-02-27
 */

#include "image.h"

/**
 *\fn SDL_Surface *imageLoad(char * file_name)
 * Charge une image
 *\param[in] file_name le nom du fichier
 *\return un pointeur sur une SDL_Surface
 */
SDL_Surface *imageLoad(char * file_name)
{
    SDL_Surface *temp = NULL;
    SDL_Surface *res = NULL;

    temp=IMG_Load(file_name);

    if(temp == NULL){
        perror("couldn't load background sprite");
        exit(errno);
    }

    res=SDL_DisplayFormat(temp);

    if(res == NULL){
        perror("couldn't load background sprite");
        exit(errno);
    }

    SDL_FreeSurface(temp);

    return res;
}

/**
 *\fn SDL_Surface *imageLoadAlpha(char * file_name)
 * Charge une image
 *\param[in] file_name le nom du fichier
 *\return un pointeur sur une SDL_Surface
 */
SDL_Surface *imageLoadAlpha(char * file_name)
{
    SDL_Surface *temp = NULL;
    SDL_Surface *res = NULL;

    temp=IMG_Load(file_name);

    if(temp == NULL){
        perror("couldn't load background sprite");
        exit(errno);
    }

    res=SDL_DisplayFormatAlpha(temp);

    if(res == NULL){
        perror("couldn't load background sprite");
        exit(errno);
    }

    SDL_FreeSurface(temp);

    return res;
}
