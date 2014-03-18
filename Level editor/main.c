#include "main.h"

int main(int argc, char* argv[]){

    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go;

    /*  Initialisation de la SDL */

    init("Level Editor");

    /*  Chargement des ressources */

    loadGame();


    /*  Appelle la fonction cleanup a la fin du programme */

    atexit(cleanup);

    go = 1;

    while(go == 1){

    /*  Vérifiaction de l'etat des entrees */

        getInput();

    /*  Mise a jour du jeu */

        update();

    /*  Affichage du jeu */
        SDL_FillRect(jeu.screen, NULL, SDL_MapRGB(jeu.screen->format, TRANS_R, TRANS_G, TRANS_B));

        draw();

    /*  Gestion des fps (60 fps => delay de 16ms) */

        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;

    }


    SDL_Quit();
    return 0;

}
