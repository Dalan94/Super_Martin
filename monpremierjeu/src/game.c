/*!
 * \file game.c
 * \brief contient les fonction liées au jeu
 * \author Xavier COPONET
 * \date 2014-02-27
 */



#include "game.h"




/**
 *\fn void play(SDL_Surface *screen,char *level_name)
 *contient la boucle principale du jeu qui appelle les fonctions
 *\param[in,out] screen L'écran de jeu
 *\param[in] lvel_name le nom du niveau
 */

void play(SDL_Surface *screen, char *level_name){

    int continuer = 1;
    char charLife[5];

    /*gestion du temps*/
    char charTime[5];
    SDL_TimerID timer = NULL;
    SDL_Rect posTime={10,10,0,0}, posLife = {screen->w - 50,10,0,0};
    SDL_Color black = {0,0,0};
    int previous_time=0;
    int current_time=0;
    int old_time=201;
    int pause=0;

    int acceleration=0;
    float speed=0;


    /*définition du niveau*/
    Map *m;

    /*définition du joueur*/
    Character *player;


    /*définition des surfaces*/
    SDL_Surface *background = NULL;
    SDL_Rect posBack;
    SDL_Event event;

    /*Gestion des mouvements*/
    int move_right=0;
    int move_left=0;
    int jump = 0;

    /*Sound*/
    Sound *sound_jump = NULL;
    Sound *music=NULL;

    /*gestion des inputs*/
    Input in;
    memset(&in,0,sizeof(in));

    //effacer l'écran
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    posBack.x=0;
    posBack.y = 0;

    /*initialisation de la carte et du niveau*/
    m = initMap(screen,level_name);

    /*Gestion de la musique*/
    sound_jump =createSound();
    music=createSound();
    playMusic(music,m->lvl->music);
    soundVolume(music,0.2);

    /*Démarrage du timer */
    timer=SDL_AddTimer(1000,decomptage,&(m->lvl->timer_level));

    /*chargement de l'arrière plan*/
    background = imageLoadAlpha(m->lvl->background);

    /*initialisation du joueur*/
    player = createrCharacter("sprites/Characters/maryo_walk_r.png","sprites/Characters/maryo_walk_l.png");
    player->location.x = 5*TAILLE_BLOC;
    player->location.y = 8*TAILLE_BLOC-player->spriteR->h;


    SDL_EnableKeyRepeat(100,100); //répétition des touches

    current_time=previous_time=SDL_GetTicks();


    while(!in.key[SDLK_ESCAPE] && continuer){

        /* récupération des inputs clavier et gestion de leurs auctions*/
        updateEvents(&in);
        keyboardActionGame(&in,&move_left,&move_right,&jump,&pause,player);

        if(in.quit)
            continuer = 0;

        if(player->isOnGround && jump)
            player->isJumping = TAILLE_SAUT;
        if(!jump)
            player->isJumping = 0;
            /* ********* */

        /* gestion de la mort*/
        if(player->location.y+player->spriteL->h >= (31*TAILLE_BLOC))
            player->life = 0;
        if (old_time != m->lvl->timer_level)
        {
            if(!(m->lvl->timer_level>0 && player->life))
            {
                stopSound(music);
                printGameOver(screen,&continuer,&in);
            }else
                sprintf(charTime,"%d",m->lvl->timer_level);
            old_time=m->lvl->timer_level;
        }


        if (pause)
        {
            printPause(screen,&in,&(m->lvl->timer_level),&continuer);
            pause=0;
        }


        updateSpeed(&speed,acceleration);

        move(move_left,move_right,player,m,speed,&acceleration);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran


        printText(screen,&posTime,charTime,0,0,0,"polices/code.otf",20,0);

        sprintf(charLife,"%d",player->life);
        printText(screen,&posLife,charLife,255,100,100,"polices/code.otf",20,1);

        SDL_BlitSurface(background,NULL,screen,&posBack); // blit du background

        blitCharacter(screen,player,m);


        updateScreenMap(screen,m,"sprites/tilesetok.png"); //blit du niveau



        waitFPS(&previous_time,&current_time);

        if(!player->isJumping)
            gravity(player,m,screen);
        else
            jumping(player,m,sound_jump);

        SDL_Flip(screen);//affichage de l'écran
    } //while

    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran
    SDL_Flip(screen);

    /*Free*/
    freeSound(sound_jump);
    freeSound(music);
    SDL_FreeSurface(background);
    freeMap(m);
    SDL_RemoveTimer(timer);
}


/**
 *\fn void printGameOver(SDL_Surface *screen,int *continuer,Input *in)
 *affiche le message de game overflow_error
 *\param[out] screen l'écran de jeu
 */
void printGameOver(SDL_Surface *screen,int *continuer,Input *in){
    SDL_Surface *gameOver = NULL;
    SDL_Rect posGame;


    Sound *s;
    s = createSound();
    playMusic(s,"sound/chopin1.mp3");

    gameOver = IMG_Load("sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(gameOver, SDL_SRCALPHA, 200);
    SDL_BlitSurface(gameOver,NULL,screen,&posGame);

    printText(screen,NULL,"GAME OVER",186,38,18,"polices/manga.ttf",65,1);
    SDL_Flip(screen);

    SDL_Delay(1500); //pause pour éviter de quitter l'écran instantanément si joueur appuit sur une touche lors de sa mort

    while(!updateEvents(in));
    *continuer = 0;
    SDL_FreeSurface(gameOver);
    freeSound(s);

}

/**
 *\fn void move (int move_left, int move_right, Character *player,Map *m, float speed)
 *  Deplace le joueur et scrolle l'ecran si besoin
 *\param[in] move_left booleen pour savoir si l'on bouge a gauche
 *\param[in] move_right booleen pour savoir si l'on bouge a droite
 *\param[in] player le joueur
 *\param[in] m la carte
 *\param[in] speed la vitesse de deplacement
 */
void move(int move_left, int move_right, Character *player,Map *m,float speed, int *acceleration)
{
    if (move_right && !move_left)
    {
        if(moveCharacter(player,RIGHT,m,speed))
        {
            (*acceleration)++;
            if (player->location.x - m->xScroll > m->screenWidth*(50-POURCENTAGE_DEPLACEMENT)/100  && player->location.x - m->xScroll < m->screenWidth*(50 + MARGE_SCROLLING-POURCENTAGE_DEPLACEMENT)/100)
                scrolling(m,RIGHT,speed);
            else if (player->location.x - m->xScroll >= m->screenWidth*(50 + MARGE_SCROLLING-POURCENTAGE_DEPLACEMENT)/100 )
                scrolling(m,RIGHT,2*speed);
        }
    }
    if (move_left && !move_right)
    {
        if(moveCharacter(player,LEFT,m,speed))
        {
            (*acceleration)++;
            if (player->location.x - m->xScroll < m->screenWidth*(50+POURCENTAGE_DEPLACEMENT)/100 && player->location.x - m->xScroll > m->screenWidth*(50 - MARGE_SCROLLING+POURCENTAGE_DEPLACEMENT)/100)
                scrolling(m,LEFT,speed);
            else if (player->location.x - m->xScroll <= m->screenWidth*(50- MARGE_SCROLLING+POURCENTAGE_DEPLACEMENT)/100)
                scrolling(m,LEFT,2*speed);
        }
    }
}

/**
 *\fn void updateSpeed(float *speed, int acceleration)
 * Met a jour la vitesse
 *\param[out] float la vitesse
 *\param[out] acceleration l'acceleration
 */
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
            *speed = 8;
            break;
        default:;
    }
}

/**
 *\fn void printPause(SDL_Surface *screen, Input *in, int *time,int *continuer)
 * Met en pause le jeu
 *\param[out] screen l'écran de jeu
 *\param[out] time le temps restant
 *\param[in] in la structure input
 *\param[out] le booléen de main loop de la fonction jouer
 */
void printPause(SDL_Surface *screen, Input *in, int *time, int *continuer)
{
    SDL_Surface *gameOver = NULL;
    SDL_Rect posGame;

    int cont = 1;
    int time_pause=*time;

    gameOver = IMG_Load("sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(gameOver, SDL_SRCALPHA, 200);
    SDL_BlitSurface(gameOver,NULL,screen,&posGame);


    printText(screen,NULL,"PAUSE",186,38,18,"polices/manga.ttf",65,1);
    SDL_Flip(screen);
    in->key[SDLK_p] = 0;

    while(!in->key[SDLK_p] && *continuer){

        updateEvents(in);
        if(in->quit)
            *continuer = 0;

    }
    SDL_FreeSurface(gameOver);

    *time=time_pause;
    in->key[SDLK_p] = 0;
}

Uint32 decomptage(Uint32 intervalle,void* parametre){
    int *time = parametre;
    (*time)--;
    return intervalle;
}