/*!
 * \file jeu.c
 * \brief contient les fonction liées au jeu
 * \author Xavier COPONET
 * \date 2014-02-27
 */


#include "jeu.h"



/**
 *\fn void jouer(SDL_Surface *screen,char *level_name)
 *contient la boucle principale du jeu qui appelle les fonctions
 *\param[in,out] screen L'écran de jeu
 *\param[in] lvel_name le nom du niveau
 */

void jouer(SDL_Surface *screen, char *level_name){

    int continuer = 1;

    /*gestion du temps*/
    int time = 200;
    char timeChar[5];
    SDL_TimerID timer = SDL_AddTimer(1000,decomptage,&time); /*initialiation et Démarrage du timer */
    SDL_Rect posTime={10,10,0,0};
    SDL_Color black = {0,0,0};
    int previous_time=0;
    int current_time=0;
    int event_appear=1;
    int old_time=201;
    int acceleration=0;
    float speed=0;

    /*définition du niveau*/
    Map *m;
    Level *lvl;

    /*définition du joueur*/
    Character *player;


    /*définition des surfaces*/
    SDL_Surface *background = NULL;
    SDL_Rect posBack;
    SDL_Event event;

    /*Gestion des mouvements*/
    int move_right=0;
    int move_left=0;

    //effacer l'écran
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    posBack.x=0;
    posBack.y = 0;

    /*initialisation de la carte et du niveau*/
    lvl = openLevel(level_name);
    m = initMap(lvl,screen);

    /*chargement des différentes sprites*/
    background = IMG_Load(m->lvl->background);

    if(background == NULL){
        perror("couldn't load background sprite");
        exit(errno);
    }

    /*initialisation du joueur*/
    player = createrCharacter("sprites/Characters/maryo_walk_r.png","sprites/Characters/maryo_walk_l.png");
    player->location.x = 5*TAILLE_BLOC;
    player->location.y = 2*TAILLE_BLOC-player->spriteR->h-2;


    SDL_EnableKeyRepeat(100,100); //répétition des touches

    current_time=previous_time=SDL_GetTicks();


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
                        if (player->isJumping > TAILLE_SAUT - 4 || (player->isJumping == 0 && player->isOnGround))
                            move_right=1;
                        break;

                    case SDLK_LEFT:
                        if (player->isJumping > TAILLE_SAUT - 4 || (player->isJumping == 0 && player->isOnGround))
                            move_left=1;
                        break;

                    case SDLK_SPACE:
                        if(player->isOnGround)
                            player->isJumping = TAILLE_SAUT;
                        break;
                    default: ;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        move_right=0;
                        acceleration=0;
                        break;
                    case SDLK_LEFT:
                        move_left=0;
                        acceleration=0;
                        break;
                    case SDLK_SPACE:
                        player->isJumping = 0;
                        break;
                    default: ;
                }

            default: event_appear = 0;
        }

        if (old_time != time)
        {
            if(time>0){
                sprintf(timeChar,"%d",time);
            }else{
                printGameOver(screen,&continuer);
            }
            old_time=time;

            event_appear = 1;
        }

        //if(event_appear)
        {
            updateSpeed(&speed,acceleration);

            move(move_left,move_right,player,m,speed,&acceleration);

            SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran

            printText(screen,&posTime,timeChar,black,"polices/code.otf",20,0);

            SDL_BlitSurface(background,NULL,screen,&posBack); // blit du background


            blitCharacter(screen,player,m);

            updateScreenMap(screen,m); //blit du niveau
        }

        waitFPS(&previous_time,&current_time);

        if(!player->isJumping)
            gravity(player,m,screen);
        else
            jumping(player,m);

       // if(event_appear)
            SDL_Flip(screen);//affichage de l'écran

        event_appear = 1;
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
    SDL_Surface *grass1, *ground1,*grey_wall;


    /* ********************************************* */

    /*chargement des sprites*/
    grass1 = IMG_Load("sprites/herbe.bmp");
    ground1 = IMG_Load("sprites/ground1.bmp");
    grey_wall = IMG_Load("sprites/grey_wall.png");


    if(grass1 == NULL || ground1 == NULL || grey_wall == NULL){
        perror("couldn't load sprite(s)");
        exit(errno);
    }

    minx = m->xScroll/TAILLE_BLOC-1;
    maxx = (m->xScroll + m->screenWidth)/TAILLE_BLOC+1;
    nbRow = m->screenHeight/TAILLE_BLOC;

    /*mise à jour de la surface screen*/
    for(i=minx;i<maxx;i++){
        for(j=0;j<nbRow;j++){
            pos.x = (i+1)*TAILLE_BLOC-m->xScroll;
            pos.y = j*TAILLE_BLOC;

            if(i>=0 && i<m->lvl->width){
                switch(m->lvl->map[j][i]){
                    case VOID:
                        break;

                    case GRASS1:
                        SDL_BlitSurface(grass1,NULL,screen,&pos);
                        break;
                    case GROUND1 :
                        SDL_BlitSurface(ground1,NULL,screen,&pos);
                        break;
                    case GREY_WALL :
                        SDL_BlitSurface(grey_wall,NULL,screen,&pos);
                        break;
                    default: ;
                    }
            }
        }
    }

    SDL_FreeSurface(grass1);
    SDL_FreeSurface(ground1);
    SDL_FreeSurface(grey_wall);
}

/**
 *\fn void scrolling(Map *m,int direction,float speed)
 *effectue un scrolling
 *\param[in,out] map Le niveau à gérer
 *\param[in] direction La direction de scrolling
 *\param[in] speed la vitesse de scrolling
 */
void scrolling(Map *m, int direction,float speed){
    switch (direction){
        case RIGHT:
            if(m->xScroll < (m->lvl->width+1)*TAILLE_BLOC-m->screenWidth)
                m->xScroll+= speed;
            break;

        case LEFT:
            if(m->xScroll > TAILLE_BLOC)
                m->xScroll-= speed;
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
 *\fn  Map *initMap(Level *lvl,SDL_Surface *screen){
 *initialise la carte
 *\param[in] screen l'écran de jeu
 *\param[in] level le niveau
 *\return un pointeur sur la carte initialisée
 */
 Map *initMap(Level *lvl,SDL_Surface *screen){
    Map *m;

    m = (Map *)malloc(sizeof(Map));
    if (m == NULL){
        perror("allocation error");
        exit(errno);
    }
    m->lvl=lvl;
    m->screenHeight = screen->h;
    m->screenWidth = screen->w;
    m->xScroll = 20;

    return m;
 }

 /**
  *\fn void freeMap(map *m)
  *désalloue la carte
  *\param[in,out] m la carte
  */
void freeMap(Map *m){
    closeLevel(m->lvl);
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

/**
 *\fn void move (int move_left, int move_right, Character *player,Map *m, float speed)
 *  Deplace le joueur et scrolle l'ecran si besoin
 *\param[in] move_left booleen pour savoir si l'on bouge a gauche
 *\param[in] move_right booleen pour savoir si l'on bouge a droite
 *\param[in] player le joueur
 *\param[in] m la carte

 */
void move(int move_left, int move_right, Character *player,Map *m,float speed, int *acceleration)
{
    if (move_right && !move_left)
    {
        if(moveCharacter(player,RIGHT,m,speed))
        {
            (*acceleration)++;
            if (player->location.x > m->screenWidth*(50-POURCENTAGE_DEPLACEMENT)/100)
                scrolling(m,RIGHT,speed);
        }
    }
    if (move_left && !move_right)
    {
        if(moveCharacter(player,LEFT,m,speed))
        {
            (*acceleration)++;
            if (player->location.x - m->xScroll < m->screenWidth*(50+POURCENTAGE_DEPLACEMENT)/100)
                scrolling(m,LEFT,speed);
        }
    }
}

void updateSpeed(float *speed, int acceleration)
{
    switch(acceleration)
    {
        case 0:
            *speed = 1;
            break;
        case 5:
            *speed = 3;
            break;
        case 10:
            *speed = 5;
            break;
        case 15:
            *speed=7;
            break;
        case 20 :
            *speed = 10;
            break;
        default:;
    }
}
