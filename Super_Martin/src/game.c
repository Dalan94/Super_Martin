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

void play(SDL_Surface *screen, char *level_name)
{
    int continuer = 1;

    SDL_TimerID timer = NULL;

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
    list playerList;

    /*définition des ennemis*/
    list enemiesList;



    /*définition des surfaces*/
    SDL_Surface *background = NULL;
    SDL_Rect posBack;


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
    soundVolume(music,0);

    /*Démarrage du timer */
    timer=SDL_AddTimer(1000,decomptage,&(m->lvl->timer_level));

    /*chargement de l'arrière plan*/
    background = imageLoadAlpha(m->lvl->background);

    /*initialisation du joueur*/
    player = createrCharacter("sprites/Characters/maryo.png",5*TAILLE_BLOC,8*TAILLE_BLOC-39,0);
    initList(&playerList);
    playerList.current = playerList.first = playerList.last = newNode(player,NULL,NULL);

    /*initialisation des ennemis*/
    initList(&enemiesList);
    createEnemy("sprites/Characters/witch_doctor.png",18*TAILLE_BLOC,19*TAILLE_BLOC-30,&enemiesList);
    createEnemy("sprites/Characters/witch_doctor.png",90*TAILLE_BLOC,19*TAILLE_BLOC-30,&enemiesList);
    createEnemy("sprites/Characters/witch_doctor.png",50*TAILLE_BLOC,19*TAILLE_BLOC-30,&enemiesList);

    SDL_EnableKeyRepeat(100,100); //répétition des touches

    current_time=previous_time=SDL_GetTicks();



    while(!in.key[SDLK_ESCAPE] && continuer){

        /* récupération des inputs clavier et gestion de leurs auctions*/
        updateEvents(&in);
        keyboardActionGame(&in,&move_left,&move_right,&jump,&pause,player,&acceleration);

        if(in.quit)
            continuer = 0;

        /* gestion de la mort*/
        if((player->location.y+player->tile->h/NB_TILE_MARYO_HEIGHT) >= m->lvl->height*TAILLE_BLOC-1)
            player->life = 0;
        if (old_time != m->lvl->timer_level || !player->life)
        {
            if(!(m->lvl->timer_level>0 && player->life))
            {
                stopSound(music);
                printGameOver(screen,&continuer,&in);
            }
            old_time=m->lvl->timer_level;
        }

        if(player->isHurt>0)
            player->isHurt--;
        else
            player->isHurt = 0;

        if((player->location.x)/TAILLE_BLOC >= m->lvl->width - IMG_END_SIZE / TAILLE_BLOC + 1 && continuer)
            printWin(screen,&continuer,&in);


        if (pause)
        {
            printPause(screen,&in,&(m->lvl->timer_level),&continuer);
            pause=0;
        }


        updateSpeed(&speed,acceleration);

        move(move_left,move_right,jump,player,m,speed,&acceleration,&enemiesList,sound_jump);
        moveEnemies(&enemiesList,m,&playerList);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran

        SDL_BlitSurface(background,NULL,screen,&posBack); // blit du background

        updateScreenMap(screen,m,m->lvl->tileSet); //blit du niveau

        blitCharacter(screen,player,m);
        blitEnnemies(screen,&enemiesList,m);

        printHUD(screen,player,m);

        waitFPS(&previous_time,&current_time);

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

    free((void *)player);
    /*freeEnemies(enemiesList);*/ /*!\bug segmentation fault*/
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
    playMusic(s,"sound/marche_funebre.mp3");
    soundVolume(s,0);

    gameOver = imageLoad("sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(gameOver, SDL_SRCALPHA, 200);
    SDL_BlitSurface(gameOver,NULL,screen,&posGame);

    printText(screen,NULL,"GAME OVER",186,38,18,"polices/manga.ttf",65,1);
    SDL_Flip(screen);

    SDL_Delay(1500); //pause pour éviter de quitter l'écran instantanément si joueur appuit sur une touche lors de sa mort

    while(!updateWaitEvents(in));
    *continuer = 0;
    SDL_FreeSurface(gameOver);
    freeSound(s);

}

/**
 *\fn void printWin(SDL_Surface *screen,int *continuer,Input *in)
 *affiche le message de reussite du niveau
 *\param[out] screen l'écran de jeu
 */
void printWin(SDL_Surface *screen,int *continuer,Input *in){
    SDL_Surface *win = NULL;
    SDL_Rect posGame;


    Sound *s;
    s = createSound();
    playMusic(s,"sound/win.mp3");

    win = imageLoad("sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(win, SDL_SRCALPHA, 200);
    SDL_BlitSurface(win,NULL,screen,&posGame);

    printText(screen,NULL,"YOU WIN !",186,38,18,"polices/sherwood.ttf",65,1);
    SDL_Flip(screen);

    SDL_Delay(1500); //pause pour éviter de quitter l'écran instantanément si joueur appuit sur une touche lors de sa mort

    while(!updateWaitEvents(in));
    *continuer = 0;
    SDL_FreeSurface(win);
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
void move(int move_left, int move_right,int jump, Character *player,Map *m,float speed, int *acceleration,list *l,Sound *jump_sound)
{
    int ret = moveCharacter(player,move_left,move_right,jump,m,speed,l,jump_sound);
    if (move_right && !move_left)
    {
        (*acceleration)++;

        {

            if (player->location.x - m->xScroll > m->screenWidth*(50-POURCENTAGE_DEPLACEMENT)/100  && player->location.x - m->xScroll < m->screenWidth*(50 + MARGE_SCROLLING-POURCENTAGE_DEPLACEMENT)/100)
                scrolling(m,RIGHT,speed);
            else if (player->location.x - m->xScroll >= m->screenWidth*(50 + MARGE_SCROLLING-POURCENTAGE_DEPLACEMENT)/100 )
                scrolling(m,RIGHT,2*speed);
        }
    }
    if (move_left && !move_right)
    {
        (*acceleration)++;

        {

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
            *speed = 2;
            break;
        case 10:
            *speed = 3;
            break;
        case 15:
            *speed=4;
            break;
        case 20 :
            *speed = MAX_SPEED;
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

    int time_pause=*time;

    gameOver = imageLoad("sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(gameOver, SDL_SRCALPHA, 200);
    SDL_BlitSurface(gameOver,NULL,screen,&posGame);


    printText(screen,NULL,"PAUSE",186,38,18,"polices/manga.ttf",65,1);
    SDL_Flip(screen);
    in->key[SDLK_p] = 0;

    while(!in->key[SDLK_p] && *continuer){

        updateWaitEvents(in);
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

/**
 *\fn void printHUD(SDL_Surface *screen,Character *player,Map *m)
 *print the player HUD on the screen
 *\param[in,out] screen the game screen
 *\param[in] player the player
 *\param[in] m the game map
 */
void printHUD(SDL_Surface *screen,Character *player,Map *m)
{
    /*life gestion*/
    char charLife[5];
    SDL_Surface *heart = NULL;
    SDL_Rect posHeart = {screen->w-105,10,0,0},posLife = {screen->w-70,10,0,0};

    /*stars gestion*/
    char charCountStars[5];
    SDL_Surface *stars = NULL;
    SDL_Rect posStars ={screen->w/2,3,0,0}, posCountStars ={screen->w/2+40,10,0,0};

    /*time gestion*/
    char charTime[5];
    SDL_Rect posTime={40,10,0,0};
    SDL_Surface *watch;
    SDL_Rect posWatch = {10,10,0,0};

    /*sprites loading*/
    heart = imageLoadAlpha("sprites/Heart.png");
    watch = imageLoadAlpha("sprites/watch.png");
    stars = imageLoadAlpha("sprites/stars.png");
     if(stars == NULL)
    {
        perror("error while loading stars sprite");
        exit(errno);
    }

    if(heart == NULL)
    {
        perror("error while loading heart sprite");
        exit(errno);
    }

    if(watch == NULL)
    {
        perror("error while loading watch sprite");
        exit(errno);
    }
    sprintf(charTime,"%d",m->lvl->timer_level);

    /*affichage temps*/
    printText(screen,&posTime,charTime,0,0,0,"polices/code.otf",20,0);
    SDL_BlitSurface(watch,NULL,screen,&posWatch);
    /* ***** */

    /*affichage de la vie*/
    sprintf(charLife,"%d %d",player->life,player->isHurt);
    printText(screen,&posLife,charLife,255,100,100,"polices/code.otf",20,1);
    SDL_BlitSurface(heart,NULL,screen,&posHeart);

    /*affichage du nombre d'étoiles récoltées*/
    sprintf(charCountStars,"%d",player->countStars);
    printText(screen,&posCountStars,charCountStars,0,0,0,"polices/code.otf",20,1);
    SDL_BlitSurface(stars,NULL,screen,&posStars);

    SDL_FreeSurface(heart);
    SDL_FreeSurface(watch);
    SDL_FreeSurface(stars);

}
