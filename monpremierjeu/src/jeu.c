/*!
 * \file jeu.c
 * \brief contient les fonction liées au jeu
 * \author Xavier COPONET
 * \date 2014-02-27
 */


#include "jeu.h"



/**
 *\fn void jouer(SDL_Surface *screen)
 *contient la boucle principale du jeu qui appelle les fonctions
 *\param[in,out] screen L'écran de jeu
 */

void jouer(SDL_Surface *screen){

    int continuer = 1 ,i,j;

    /*gestion du temps*/
    int time = 10;
    char timeChar[5];
    SDL_TimerID timer = SDL_AddTimer(1000,decomptage,&time); /*initialiation et Démarrage du timer */
    SDL_Rect posTime={10,10,0,0};
    SDL_Color black = {0,0,0};

    /*définition du niveau*/
    Map *m;


    /*définition des surfaces*/
    SDL_Surface *background = NULL;
    SDL_Rect posBack;
    SDL_Event event;

    //effacer l'écran
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    posBack.x=0;
    posBack.y = 0;

    /*initialisation de la carte */
    m = initMap(64,24,screen);

    /*ligne d'herbe*/
    for(i=0;i<m->nbBlocLg;i++){
        m->lvl[i][19] = GRASS1;
    }

    /*terre*/
    for (i = 0; i<m->nbBlocLg; i++){
        for(j = 20; j<m->nbBlocHt; j++){
            m->lvl[i][j] = GROUND1;
        }
    }
    m->lvl[23][20] = VOID;
    m->lvl[45][23] = VOID;
    /* ****************************** */

    /*chargement des différentes sprites*/
    background = IMG_Load("sprites/game-background.jpg");

    if(background == NULL){
        perror("couldn't load background sprite");
        exit(errno);
    }

    SDL_EnableKeyRepeat(100,100); //répétition des touches


    while(continuer){
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;

                    case SDLK_RIGHT:
                        scrolling(m,RIGHT);
                        break;

                    case SDLK_LEFT:
                        scrolling(m,LEFT);
                        break;
                    default: ;
                }
            break;
            default: ;
        }
        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran

        SDL_BlitSurface(background,NULL,screen,&posBack); // blit du background

        /*blit de peach*/
       /* if(isPeachR)
            SDL_BlitSurface(peachR, NULL, screen, &posPeach);
        else
            SDL_BlitSurface(peachL, NULL, screen, &posPeach);*/

        updateScreenMap(screen,m); //blit du niveau
        if(time>0){
            sprintf(timeChar,"%d",time);
            printText(screen,&posTime,timeChar,black,"polices/code.otf",20,0);
        }else{
            printGameOver(screen,&continuer);
        }


        SDL_Flip(screen);//affichage de l'écran
        //SDL_Delay(60);


    } //while

    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran
    SDL_Flip(screen);


    SDL_FreeSurface(background);

    freeMap(m);
    SDL_RemoveTimer(timer);
}

/**
 *\fn void updateScreenMap(SDL_Surface *screen, SDL_Surface **lvl,int col,int nbCol)
 *met à jour l'écran avec les données de la carte (ignore les personnages)
 *\param[in,out] screen l'écran
 *\param[in] lvl le niveau.
 *\param[in] col la première colonne à afficher
 *\param[in] nbCol le nombre de colonnes à afficher (nombre de colonnes de la fenêtre)
 *\param[in] nbRow le nombre de lignes à afficher (nombre de lignes de la fenêtre)
 */
void updateScreenMap(SDL_Surface *screen, Map *m){
    int i,j;
    int minx,maxx,nbRow;
    SDL_Rect pos; //position de la sprite à blit

    /*liste des sprites ayant possibilité d'être affichées*/
    SDL_Surface *grass1, *ground1;


    /* ********************************************* */

    /*chargement des sprites*/
    grass1 = IMG_Load("sprites/herbe.bmp");
    ground1 = IMG_Load("sprites/ground1.bmp");


    if(grass1 == NULL || ground1 == NULL){
        perror("couldn't load sprite(s)");
        exit(errno);
    }

    minx = m->xScroll/TAILLE_BLOC-1;
    maxx = (m->xScroll + m->screenWidth)/TAILLE_BLOC+1;
    nbRow = m->screenHeight/TAILLE_BLOC;

    /*mise à jour de la surface screen*/
    for(i=minx;i<maxx;i++){
        for(j=0;j<nbRow;j++){
            pos.x = i*TAILLE_BLOC-m->xScroll;
            pos.y = j*TAILLE_BLOC;

            if(i>0 && i<m->nbBlocLg){
                switch(m->lvl[i][j]){
                    case VOID:
                        break;

                    case GRASS1:
                        SDL_BlitSurface(grass1,NULL,screen,&pos);
                        break;
                    case GROUND1 :
                        SDL_BlitSurface(ground1,NULL,screen,&pos);
                        break;
                    default: ;
                    }
            }
        }
    }

    SDL_FreeSurface(grass1);
    SDL_FreeSurface(ground1);
}

/**
 *\fn void scrolling(Map *m,int direction)
 *effectue un scrolling
 *\param[in,out] map Le niveau à gérer
 *\param[in] direction La direction de scrolling
 */
void scrolling(Map *m, int direction){
    switch (direction){
        case RIGHT:
            if(m->xScroll < m->nbBlocLg*TAILLE_BLOC-m->screenWidth)
                m->xScroll+=2;
            break;

        case LEFT:
            if(m->xScroll > TAILLE_BLOC)
                m->xScroll-=2;
            break;
        default: ;
    }
}

Uint32 decomptage(Uint32 intervalle,void* parametre){
    int *time = parametre;
    (*time)--;
    return intervalle;
}

/**
 *\fn void initMap(int nbBlocLgMap, int nbBloHtMap,SDL_Surface *screen)
 *initialise la carte

 *\param[in] nbBlocLgMap Le nombre de bloc dans la largeur de la carte
 *\param[in] nbBlocHtMap Le nombre de bloc dans la hauteur de la carte
 *\param[in] screen l'écran de jeu
 *\return un pointeur sur la carte initialisée
 */
 Map *initMap(int nbBlocLgMap, int nbBlocHtMap,SDL_Surface *screen){
    Map *m;
    int i,j;

    m = (Map *)malloc(sizeof(Map));
    if (m == NULL){
        perror("allocation error");
        exit(errno);
    }
    m->lvl = (unsigned char **) malloc(nbBlocLgMap*sizeof(char*));
    for(i = 0;i<nbBlocLgMap;i++)
        m->lvl[i] = (unsigned char *)malloc(nbBlocHtMap*sizeof(char));
    if(m->lvl == NULL){
        perror("allocation error");
        exit(errno);
    }


    m->nbBlocHt = nbBlocHtMap;
    m->nbBlocLg = nbBlocLgMap;
    m->screenHeight = screen->h;
    m->screenWidth = screen->w;
    m->xScroll = 20;

    /*initialation à VOID*/
    for (i = 0; i<nbBlocLgMap; i++){
        for(j = 0; j<nbBlocHtMap; j++){
            m->lvl[i][j] = VOID;
        }
    }

    return m;
 }

 /**
  *\fn void freeMap(map *m)
  *désalloue la carte
  *\param[in,out] m la carte
  */
void freeMap(Map *m){
    int i;

    for(i = 0;i<m->nbBlocLg;i++){
        free((void *)m->lvl[i]);
    }
    free((void *)m->lvl);
    free((void *)m);
}


/**
 *\fn void printGameOver(SDL_Surface *screen,int *continuer)
 *affiche le message de game overflow_error
 *\param[out] screen l'écran de jeu
 */
void printGameOver(SDL_Surface *screen,int *continuer){
    SDL_Surface *gameOver = NULL;
    SDL_Rect posGame, posText;
    SDL_Color color = {186,38,18};
    int cont = 1;
    SDL_Event event;

    Sound *s;
    s = createSound();
    playMusic(s,"sound/chopin1.mp3");

    gameOver = IMG_Load("sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(gameOver, SDL_SRCALPHA, 200);
    SDL_BlitSurface(gameOver,NULL,screen,&posGame);

    posText.x = screen->w/2-150;
    posText.y = screen->h/2-65;

    printText(screen,&posText,"GAME OVER",color,"polices/manga.ttf",65,1);
    SDL_Flip(screen);

    SDL_Delay(1500); //pause pour éviter de quitter l'écran instantanément si joueur appuit sur une touche lors de sa mort

    while(cont){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                cont = 0;
                break;
            case SDL_KEYDOWN:
                cont = 0;
                break;
            default:
                ;
        }
    }
    *continuer = 0;
    freeSound(s);

}
