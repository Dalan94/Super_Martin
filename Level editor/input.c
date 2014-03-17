#include "input.h"


void getInput(){

    SDL_Event event;

/*  Keymapping :
*   Gere les input clavier et les enregistre
*/

    while(SDL_PollEvent(&event)){


        switch(event.type){

            case SDL_QUIT :

                exit(0);
                break;

            case SDL_KEYDOWN :

                switch(event.key.keysym.sym){

                    case SDLK_ESCAPE :

                        exit(0);
                        break;

                    case SDLK_DELETE :

                        input.reinit = 1;
                        break;


                    case SDLK_q :

                        input.left = 1;
                        break;

                    case SDLK_d :

                        input.right = 1;
                        break;

                    case SDLK_z :

                        input.up = 1;
                        break;

                    case SDLK_s :

                        input.down = 1;
                        break;

                    case SDLK_k :

                        input.save = 1;
                        break;

                    case SDLK_l :

                        input.load = 1;
                        break;

                    default :

                        break;
                }
                break;

            case SDL_KEYUP :

                switch(event.key.keysym.sym){

                    case SDLK_q :

                        input.left = 0;
                        break;

                    case SDLK_d :

                        input.right = 0;
                        break;

                    case SDLK_z :

                        input.up = 0;
                        break;

                    case SDLK_s :

                        input.down = 0;
                        break;

                    default :

                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN :

                switch(event.button.button){

                    case SDL_BUTTON_LEFT :

                        input.add = 1;
                        break;

                    case SDL_BUTTON_MIDDLE :

                        input.remove = 1;
                        break;

                    case SDL_BUTTON_RIGHT :

                        input.copy = 1;
                        break;

                    case SDL_BUTTON_WHEELUP :

                        input.next = 1;
                        break;

                    case SDL_BUTTON_WHEELDOWN :

                        input.previous = 1;
                        break;

                    default :

                        break;
                }
                break;

            case SDL_MOUSEBUTTONUP :

                switch(event.button.button){

                    case SDL_BUTTON_LEFT :

                        input.add = 0;
                        break;

                    case SDL_BUTTON_MIDDLE :

                        input.remove = 0;
                        break;

                    default :

                        break;
                }
                break;
        }
    }


    /*  Enregistrement des coordonnees de la souris */

    SDL_GetMouseState(&input.mouseX, &input.mouseY);

    /*  Obtention des coordonnees de la tile pointee par la souris */

    input.mouseX /= TILE_SIZE;
    input.mouseY /= TILE_SIZE;

    input.mouseX *= TILE_SIZE;
    input.mouseY *= TILE_SIZE;
}


void update(void){



    /*  Recuperation des coordonnees de la souris */

    cursor.x = input.mouseX;
    cursor.y = input.mouseY;

    /*  Gestion du scrolling */

    if(input.left == 1){

        map.startX -= (TILE_SIZE);

        if(map.startX < 0){

            map.startX = 0;
        }
    }

    else if(input.right == 1){

        map.startX += (TILE_SIZE);

        if(map.startX + SCREEN_WIDTH >= map.maxX){

            map.startX = map.maxX - SCREEN_WIDTH;
        }
    }

    if(input.up == 1){

        map.startY -= TILE_SIZE;

        if(map.startY < 0){

            map.startY = 0;
        }
    }

    else if(input.down == 1){

        map.startY += TILE_SIZE;

        if(map.startY + SCREEN_HEIGHT >= map.maxY){

            map.startY = map.maxY - SCREEN_HEIGHT;
        }
    }

    /*  Gestion de l'ajout de tile */

    if(input.add == 1){

        map.tile[(map.startY + cursor.y) / TILE_SIZE][(map.startX + cursor.x) / TILE_SIZE] = cursor.tileID;
    }

    /*  Gestion de la suppression d'une tile */

    else if(input.remove == 1){

        map.tile[(map.startY + cursor.y) / TILE_SIZE][(map.startX + cursor.x) / TILE_SIZE] = BLANK_TILE;
        cursor.tileID = 0;
    }

    /*  Defilement du choix de tile */

    if(input.previous == 1){

        cursor.tileID--;

        if(cursor.tileID < 0){

            cursor.tileID = MAX_TILES - 1;
        }

        else if(cursor.tileID > MAX_TILES){

            cursor.tileID = 0;
        }

        input.previous = 0;
    }

    if(input.next == 1){

        cursor.tileID++;

        if(cursor.tileID < 0){

            cursor.tileID = MAX_TILES - 1;
        }

        else if(cursor.tileID > MAX_TILES){

            cursor.tileID = 0;
        }

        input.next = 0;
    }

    /*  Gestion de la copie de tile */

    if(input.copy == 1){

        cursor.tileID = map.tile[(map.startY + cursor.y) / TILE_SIZE][(map.startX + cursor.x) / TILE_SIZE];
        input.copy = 0;
    }

    /* Gestion de la reinitialisation de la map */

    if(input.reinit == 1){

        reinitMap("sprites/Tuto/Map/map1.txt");
        loadMap("sprites/Tuto/Map/map1.txt");
        input.reinit = 0;
    }

    /*  Gestion de la suavegarde de la map */

    if(input.save == 1){

        saveMap("sprites/Tuto/Map/test1.lvl");
        input.save = 0;
    }

    /*  Gestion de chargement de la map */

    if(input.load == 1){

        loadMap("sprites/Tuto/Map/map4.txt");
        input.load = 0;
    }

    /*  Ajout d'un delai pour ralentir le scrolling */

    if(input.left == 1 || input.right == 1 || input.up == 1 || input.down ==1){

        SDL_Delay(30);
    }
}
