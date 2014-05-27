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

void blitColor(Uint32 red, Uint32 green,Uint32 blue, int alpha,SDL_Surface *screen)
{
    SDL_Rect pos;
    SDL_Surface *surface = SDL_CreateRGBSurface(SDL_SRCALPHA | SDL_HWSURFACE | SDL_SRCCOLORKEY,SCREEN_WIDTH,SCREEN_HEIGHT,8,0,0,0,0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, red, green, blue));
    pos.x = pos.y = 0;
    SDL_SetAlpha(surface, SDL_SRCALPHA, alpha);
    SDL_BlitSurface(surface,NULL,screen,&pos);
    SDL_FreeSurface(surface);
}
