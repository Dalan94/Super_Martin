#include "draw.h"

void drawImage(SDL_Surface *image, int x, int y){

    SDL_Rect dest;

    /* Reglage du rectangle a blitter selon la taille de l'image source */

    dest.x = x;
    dest.y = y;
    dest.w = image->w;
    dest.h = image->h;

    /* Blitte l'image entiere sur l'ecran aux coordonnees x et y */

    SDL_BlitSurface(image, NULL, jeu.screen, &dest);
}


void drawTile(SDL_Surface *image, int destx, int desty, int srcx, int srcy){

    SDL_Rect dest, src;

    /* Reglage du rectangle a blitter selon la taille de l'image source */

    dest.x = destx;
    dest.y = desty;
    dest.w = TILE_SIZE;
    dest.h = TILE_SIZE;

    /* Rectangle source a blitter */

    src.x = srcx;
    src.y = srcy;
    src.w = TILE_SIZE;
    src.h = TILE_SIZE;

    /* Blitte l'image entiere sur l'ecran aux coordonnees x et y */

    SDL_BlitSurface(image, &src, jeu.screen, &dest);
}



void draw(void){

    /*  Affiche le fond aux coordonnees (0.0) */

    drawImage(map.background, 0, 0);

    /*  Affichage de la map */

    drawMap("sprites/Tuto/Tiles/tilesetok.png");

    /*  Affichage de l'ecran */

    SDL_Flip(jeu.screen);

    /* Ajout d'un delai */

    SDL_Delay(1);
}

SDL_Surface *loadImage(char *name){

/*  Chargement d'une image temporaire */
    SDL_Surface *tmp;
    SDL_Surface *image;
    tmp = IMG_Load(name);

/*  Arret du programme si erreur */

    if(tmp == NULL){

        printf("Failed to load image %s\n", name);
        return NULL;
    }

/*  Gestion de la transparence */



/*  Conversion de l'image au format de l'ecran */

    image = SDL_DisplayFormatAlpha(tmp);

/*  Liberation de l'image temporaire */

    SDL_FreeSurface(tmp);

    if(image == NULL){

        printf("Failed to convert image %s to native format\n", name);
        return NULL;
    }

    return image;
}

void delay(unsigned int frameLimit){

/* Gestion des 60 fps */

    unsigned int ticks = SDL_GetTicks();

    if(frameLimit < ticks){

        return;
    }

    if(frameLimit > ticks + 16){

        SDL_Delay(16);
    }

    else{

        SDL_Delay(frameLimit - ticks);
    }
}


