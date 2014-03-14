/*!
 * \file text.c
 * \brief contient les fonction pour afficher du texte à l'écran
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#include "text.h"

/**
 *\fn void printText(SDL_Surface *screen, SDL_Rect *posText, char *text, SDL_Color color, char *font,int ptSize,int mode)
 *affiche le texte sur l'écran à la position donnée
 *\param[out] screen L'écran
 *\param[in] posText La position du texte à afficher
 *\param[in] text Le texte à afficher
 *\param[in] color la couleur du texte
 *\param[in] font L'adresse de la police d'affichage (.ttf)
 *\param[in] ptSize la taille du texte à afficher
 *\param[in] mode Le mode d'écriture : 0 (Solid), 1 (Blended)
 */
void printText(SDL_Surface *screen, SDL_Rect *posText, char *text, SDL_Color color, char *font,int ptSize,int mode){

    SDL_Surface *textSurface = NULL;

    /*chargement de TTF*/
    TTF_Init();

    TTF_Font *ttfFont = TTF_OpenFont(font,ptSize);//chargement de la police
    if(ttfFont == NULL){
        perror("error while loading font");
        exit(errno);
    }

    switch (mode){
        case 0:
            textSurface = TTF_RenderText_Solid(ttfFont,text,color);
            break;
        case 1:
            textSurface = TTF_RenderText_Blended(ttfFont, text, color);
            break;
        default:
            printf("unknown writing mode");
            exit(EXIT_FAILURE);
    }
    if(textSurface == NULL){
        fprintf(stderr,"writing error");
        exit(EXIT_FAILURE);
    }

    SDL_BlitSurface(textSurface, NULL, screen, posText);

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(ttfFont);
    TTF_Quit();
}
