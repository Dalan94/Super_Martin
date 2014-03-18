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
    char timeChar[5];
    SDL_TimerID timer = NULL;
    SDL_Rect posTime={10,10,0,0};
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

        /* récupération des inputs clavier*/
        updateEvents(&in);
        keyboardActionGame(&in,&move_left,&move_right,&jump,&pause,player);
        /* ******** */

        if(player->isOnGround && jump)
            player->isJumping = TAILLE_SAUT;
        if(!jump)
            player->isJumping = 0;

        if (old_time != m->lvl->timer_level)
        {
            if(m->lvl->timer_level>0){
                sprintf(timeChar,"%d",m->lvl->timer_level);
            }else{
                stopSound(music);
                printGameOver(screen,&continuer);
            }
            old_time=m->lvl->timer_level;
        }

        if (pause)
        {
            printPause(screen,&event,&(m->lvl->timer_level));
            pause=0;
        }


        updateSpeed(&speed,acceleration);

        move(move_left,move_right,player,m,speed,&acceleration);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran

        printText(screen,&posTime,timeChar,black,"polices/code.otf",20,0);

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
 *\fn void printGameOver(SDL_Surface *screen,int *continuer)
 *affiche le message de game overflow_error
 *\param[out] screen l'écran de jeu
 */
void printGameOver(SDL_Surface *screen,int *continuer){
    SDL_Surface *gameOver = NULL;
    SDL_Rect posGame;
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

    printText(screen,NULL,"GAME OVER",color,"polices/manga.ttf",65,1);
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
            *speed = 10;
            break;
        default:;
    }
}

/**
 *\fn void printPause(SDL_Surface *screen, SDL_Event *event, int *time)
 * Met en pause le jeu
 *\param[out] screen l'écran de jeu
 *\param[out] time le temps restant
 *\param[out] event l'evenement en cours
 */
void printPause(SDL_Surface *screen, SDL_Event *event, int *time){
    SDL_Surface *gameOver = NULL;
    SDL_Rect posGame;
    SDL_Color color = {186,38,18};
    int cont = 1;
    int time_pause=*time;

    gameOver = IMG_Load("sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(gameOver, SDL_SRCALPHA, 200);
    SDL_BlitSurface(gameOver,NULL,screen,&posGame);


    printText(screen,NULL,"PAUSE",color,"polices/manga.ttf",65,1);
    SDL_Flip(screen);

    //SDL_Delay(500); //pause pour éviter de quitter l'écran instantanément si joueur appuit sur une touche lors de sa mort

    while(cont){
        SDL_WaitEvent(event);
        switch(event->type){
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
    SDL_FreeSurface(gameOver);

    *time=time_pause;
}

Uint32 decomptage(Uint32 intervalle,void* parametre){
    int *time = parametre;
    (*time)--;
    return intervalle;
}
