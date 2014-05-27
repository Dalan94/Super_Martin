/*!
 * \file image.c
 * \brief Contain the functions managing the images
 * \author Rémi BERTHO
 * \date 2014-02-27
 */

#include "image.h"

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

SDL_Surface *imageLoadAlpha(char * file_name)
{
    SDL_Surface *temp = NULL;
    SDL_Surface *res = NULL;

    temp=IMG_Load(file_name);

    if(temp == NULL)
    {
        perror("couldn't load sprite");
        exit(errno);
    }

    res=SDL_DisplayFormatAlpha(temp);

    if(res == NULL)
    {
        perror("couldn't load sprite");
        exit(errno);
    }

    SDL_FreeSurface(temp);

    return res;
}
