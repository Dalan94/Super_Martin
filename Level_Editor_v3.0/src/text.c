/*!
 * \file text.c
 * \brief contient les fonction pour afficher du texte à l'écran
 * \author Xavier COPONET
 * \date 2014-02-27
 */

#include "text.h"

/**
 *\fn void printText(SDL_Surface *screen, SDL_Rect *posText, char *text, int r,int g, int b, char *font,int ptSize,int mode)
 *affiche le texte sur l'écran à la position donnée
 *\param[out] screen L'écran
 *\param[in] posText La position du texte à afficher ; si NULL, centré en largeur et hauteur
 *\param[in] text Le texte à afficher
 *\param[in] int r red value
 *\param[in] int g green value
 *\param[in] int b blue value
 *\param[in] font L'adresse de la police d'affichage (.ttf)
 *\param[in] ptSize la taille du texte à afficher
 *\param[in] mode Le mode d'écriture : 0 (Solid), 1 (Blended)
 */
void printText(SDL_Surface *screen, SDL_Rect *posText, char *text, int r,int g, int b, char *font,int ptSize,int mode)
{

    SDL_Surface *textSurface = NULL;
    SDL_Color color = {r,g,b};
    int allocateSDL_Rect = 0;

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

    if(posText == NULL){
        allocateSDL_Rect = 1;
        posText = (SDL_Rect *) malloc(sizeof(SDL_Rect));
        posText->h = posText->w = 0;
        posText->x = screen->w/2-textSurface->w/2;
        posText->y = screen->h/2-textSurface->h/2;
    }

    if(posText->x == -1)
        posText->x = screen->w/2-textSurface->w/2;

    SDL_BlitSurface(textSurface, NULL, screen, posText);


    SDL_FreeSurface(textSurface);
    TTF_CloseFont(ttfFont);
    TTF_Quit();
    if(allocateSDL_Rect)
        free((void *)posText);

}

void captureText(SDL_Surface *screen, SDL_Rect posText,char *text, int text_length, int r, int g, int b, char *font, int text_size,  int *go)
{
    int i = 0, j, posX = posText.x, posY = posText.y, ret=1;
    SDL_Surface *screenshot;
    SDL_Rect posWait;

    screenshot = SDL_DisplayFormatAlpha(screen);
    SDL_SetAlpha(screenshot, SDL_SRCALPHA, 200);
    posWait.x = posWait.y = 0;
    Input in;
    memset(&in, 0, sizeof(in));

    while(*go && ret)
    {
        updateWaitEvents(&in);
        if(in.key[SDLK_ESCAPE])
        {
            *go = 0;
            in.key[SDLK_ESCAPE] = 0;

        }
        else if(in.key[SDLK_RETURN])
        {
            ret = 0;
            in.key[SDLK_RETURN] = 0;
        }
        else
        {
            for(j = SDLK_UNDERSCORE ; j <= SDLK_KP9; j++)
            {
                if(in.key[j])
                {
                    if((in.key[SDLK_CAPSLOCK] || in.key[SDLK_RSHIFT] || in.key[SDLK_LSHIFT]) && j > SDLK_UNDERSCORE && j <= SDLK_z)
                    {
                        text[i] = j-32;
                        text[i+1] = 0;
                        in.key[j] = 0;

                    }
                    else if(j >= SDLK_KP0 && j <= SDLK_KP9)
                    {
                        text[i] = j - 208;
                        in.key[j] = 0;
                    }
                    else if(j >= SDLK_UNDERSCORE && j <= SDLK_z)
                    {
                    text[i] = j;
                    text[i+1] = 0;
                    if(j != SDLK_UNDERSCORE)
                        in.key[j] = 0;
                    }
                }
            }

            if(in.key[SDLK_RSHIFT] || in.key[SDLK_LSHIFT])
            {
                if(in.key[224])
                    text[i]=48;
                if(in.key[38])
                    text[i]=49;
                if(in.key[233])
                    text[i]=50;
                if(in.key[34])
                    text[i]=51;
                if(in.key[39])
                    text[i]=52;
                if(in.key[40])
                    text[i]=53;
                if(in.key[45])
                    text[i]=54;
                if(in.key[232])
                    text[i]=55;
                if(in.key[95])
                    text[i]=56;
                if(in.key[231])
                    text[i]=57;
            }

            if(text[i] >= 32 && text[i] < SDLK_LAST && i>=0)
            {
                if(i < text_length-1)
                    i++;
                posText.x = posX;
                posText.y = posY;

                /*  Clear the display of the previous level_name */

                SDL_BlitSurface(screenshot,NULL,screen,&posWait);

                printText(screen, &posText, text, r, g, b, font, text_size, 1);
            }
            else if(in.key[SDLK_BACKSPACE] && i>= 0)
            {
                if(i>0)
                    i--;
                text[i] = 0;
                posText.x = posX;
                posText.y = posY;
                if(i==0)
                    text[0] = 32;

                /*  Clear the display of the previous level_name */

                SDL_BlitSurface(screenshot,NULL,screen,&posWait);

                /*  Display the new level_name  */

                printText(screen, &posText, text, r, g, b, font, text_size, 1);
                in.key[SDLK_BACKSPACE] = 0;
            }
        }

        SDL_Flip(screen);
    }
    SDL_FreeSurface(screenshot);
}
