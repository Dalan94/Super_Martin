/*!
 * \file game.c
 * \brief contient les fonction liées au jeu
 * \author Xavier COPONET
 * \date 2014-02-27
 */



#include "game.h"




/**
 *\fn int play(SDL_Surface *screen,char *level_name,keyConf *kc)
 *initialize a game map and contain the main loop for the game
 *\param[in,out] screen the gamin screen
 *\param[in] level_name the name of the level to be played
 *\param[in] kc the keyboard configuration structure
 *\return 1 if the player dies, 0 if he wins or if he quits the level
 */


int play(SDL_Surface *screen, char *level_name,Sound *sound_sys,int *go,SDLKey *kc)
{
    SDL_TimerID timer = NULL;

    int previous_time=0;
    int current_time=0;
    int old_time=201;
    int pause=0;
    int ret = 0;

    int acceleration=0;
    float speed=0;


    /*définition du niveau*/
    Map *m;

    /*définition du joueur*/
    Character *player;
    list playerList;

    /*définition des ennemis*/
    list enemyList;

    /*définition des plateformes*/
    platformSet ps;

    /*définition des surfaces*/
    SDL_Surface *background = NULL;
    SDL_Rect posBack;


    /*Gestion des mouvements*/
    int move_right=0;
    int move_left=0;
    int jump = 0;


    /*gestion des inputs*/
    Input in;
    memset(&in,0,sizeof(in));

    //effacer l'écran
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    posBack.x=0;
    posBack.y = 0;

    /*initialisation des ennemis*/
    initList(&enemyList);

    /*initialisation des plateformes */
    initPlatformSet(&ps);
    createPlatform(&ps,5*TILE_SIZE,5*TILE_SIZE,5*TILE_SIZE,22*TILE_SIZE);
    createPlatform(&ps,20*TILE_SIZE,15*TILE_SIZE,50*TILE_SIZE,15*TILE_SIZE);

    /*initialisation de la carte et du niveau*/
    m = initMap(screen,level_name,&enemyList);

    /*Gestion de la musique*/
    playMusic(m->lvl->music,sound_sys);

    /*Démarrage du timer */
    timer=SDL_AddTimer(1000,decomptage,&(m->lvl->timer_level));

    /*chargement de l'arrière plan*/
    background = imageLoadAlpha(m->lvl->background);

    /*initialisation du joueur*/
    player = createCharacter("sprites/Characters/maryo.png",5*TILE_SIZE,8*TILE_SIZE-39,0);
    initList(&playerList);
    playerList.current = playerList.first = playerList.last = newNode(player,NULL,NULL);




    SDL_EnableKeyRepeat(100,100); //répétition des touches

    current_time=previous_time=SDL_GetTicks();



    while(!in.key[SDLK_ESCAPE] && *go)
    {

        /* récupération des inputs clavier et gestion de leurs auctions*/
        updateEvents(&in,go);
        keyboardActionGame(&in,&move_left,&move_right,&jump,&pause,player,&acceleration,kc);

        if(in.quit)
            *go = 0;

        /* gestion de la mort*/
        if((player->location.y+player->tile->h/NB_TILE_MARYO_HEIGHT) >= m->lvl->height*TILE_SIZE-1)
            player->life = 0;
        if (old_time != m->lvl->timer_level || !player->life)
        {
            if(!(m->lvl->timer_level>0 && player->life))
            {
                stopSound(sound_sys,1);
                printGameOver(screen,go,&in,sound_sys);
                ret = 1;
                break;
            }
            old_time=m->lvl->timer_level;
            m->lvl->tileSetUse ^= 1;
        }

        if(player->isHurt>0)
            player->isHurt--;
        else
            player->isHurt = 0;


        if((player->location.x)/TILE_SIZE >= m->lvl->width - IMG_END_SIZE / TILE_SIZE + 1 && *go)
        {
            printWin(screen,go,&in,sound_sys);
            break;
        }

        if (pause)
        {
            printPause(screen,&in,&(m->lvl->timer_level),go,kc);
            pause=0;
        }


        updateSpeed(&speed,acceleration);

        movePlatform(player,&ps,&enemyList);
        move(move_left,move_right,jump,player,m,speed,&acceleration,&enemyList,sound_sys,&ps);
        moveEnemies(&enemyList,m,&playerList);

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran

        SDL_BlitSurface(background,NULL,screen,&posBack); // blit du background

        updateScreenMap(screen,m); //blit du niveau

        blitPlatform(screen,&ps,m);
        blitCharacter(screen,player,m);
        blitEnnemies(screen,&enemyList,m);

        printHUD(screen,player,m);

        waitFPS(&previous_time,&current_time);

        SDL_Flip(screen);//affichage de l'écran
    } //while

    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran
    SDL_Flip(screen);

    /*Free*/
    SDL_FreeSurface(background);
    freeMap(m);
    SDL_RemoveTimer(timer);
    stopSound(sound_sys,1);

    free((void *)player);
    freeEnemies(&enemyList);
    freeEnemies(&playerList);
    freePlatformSet(&ps);

    return ret;
}


/**
 *\fn void printGameOver(SDL_Surface *screen,int *continuer,Input *in,Sound *sound_sys)
 *print the game over screen and wait until the player press a key
 *\param[out] screen the game screen
 *\param[out] go the game function main loop validation
 *\param[in,out] in the input structure
 *\param[out] sound_sys the sound system
 */
void printGameOver(SDL_Surface *screen,int *go,Input *in,Sound *sound_sys)

{
    SDL_Surface *gameOver = NULL;
    SDL_Rect posGame;

    playMusic("sound/Colin_Newcomer_-_Funeral_March__Frederic_Chopin.mp3",sound_sys);

    gameOver = imageLoad("sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(gameOver, SDL_SRCALPHA, 200);
    SDL_BlitSurface(gameOver,NULL,screen,&posGame);

    printText(screen,NULL,"GAME OVER",186,38,18,"polices/manga.ttf",65,1);
    SDL_Flip(screen);

    SDL_Delay(1500); //pause pour éviter de quitter l'écran instantanément si joueur appuit sur une touche lors de sa mort

    while(!updateWaitEvents(in,go));
    if(in->quit)
        *go = 0;
    SDL_FreeSurface(gameOver);
    stopSound(sound_sys,1);

}

/**
 *\fn void printWin(SDL_Surface *screen,int *continuer,Input *in,Sound *sound_sys)
 *print the win screen and wait until the player press a key
 *\param[out] screen the game screen
 *\param[out] go the game function main loop validation
 *\param[in,out] in the input structure
 *\param[out] sound_sys the sound system
 */

void printWin(SDL_Surface *screen,int *go,Input *in,Sound *sound_sys)
{

    SDL_Surface *win = NULL;
    SDL_Rect posGame;

    playMusic("sound/win.mp3",sound_sys);

    win = imageLoad("sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(win, SDL_SRCALPHA, 200);
    SDL_BlitSurface(win,NULL,screen,&posGame);

    printText(screen,NULL,"YOU WIN !",186,38,18,"polices/sherwood.ttf",65,1);
    SDL_Flip(screen);

    SDL_Delay(1500); //pause pour éviter de quitter l'écran instantanément si joueur appuit sur une touche lors de sa mort

    while(!updateWaitEvents(in,go));
    if(in->quit)
        *go = 0;
    SDL_FreeSurface(win);
    stopSound(sound_sys,1);
}

/**
 *\fn void move (int move_left, int move_right, Character *player,Map *m, float speed,Sound *sound_sys)
 *  Deplace le joueur et scrolle l'ecran si besoin
 *\param[in] move_left booleen pour savoir si l'on bouge a gauche
 *\param[in] move_right booleen pour savoir si l'on bouge a droite
 *\param[in] player le joueur
 *\param[in] m la carte
 *\param[in] speed la vitesse de deplacement
 */
void move(int move_left, int move_right,int jump, Character *player,Map *m,float speed, int *acceleration,list *l,Sound *sound_sys,platformSet *ps)
{
    int ret = moveCharacter(player,move_left,move_right,jump,m,speed,l,sound_sys,ps);
    if (move_right && !move_left)
    {
        (*acceleration)++;

        {

            if (player->location.x - m->xScroll > m->screenWidth*(50-DEPLACEMENT_POURCENTAGE)/100  && player->location.x - m->xScroll < m->screenWidth*(50 + MARGE_SCROLLING-DEPLACEMENT_POURCENTAGE)/100)
                scrolling(m,RIGHT,speed);
            else if (player->location.x - m->xScroll >= m->screenWidth*(50 + MARGE_SCROLLING-DEPLACEMENT_POURCENTAGE)/100 )
                scrolling(m,RIGHT,2*speed);
        }
    }
    if (move_left && !move_right)
    {
        (*acceleration)++;

        {

            if (player->location.x - m->xScroll < m->screenWidth*(50+DEPLACEMENT_POURCENTAGE)/100 && player->location.x - m->xScroll > m->screenWidth*(50 - MARGE_SCROLLING+DEPLACEMENT_POURCENTAGE)/100)
                scrolling(m,LEFT,speed);
            else if (player->location.x - m->xScroll <= m->screenWidth*(50- MARGE_SCROLLING+DEPLACEMENT_POURCENTAGE)/100)
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
 *\fn void printPause(SDL_Surface *screen, Input *in, int *time,int *go, SDLKey *kc)
 * Met en pause le jeu
 *\param[out] screen l'écran de jeu
 *\param[out] time le temps restant
 *\param[in] in la structure input
 *\param[out] go le booléen de main loop de la fonction jouer
 */
void printPause(SDL_Surface *screen, Input *in, int *time, int *go,SDLKey *kc)
{
    SDL_Surface *gameOver = NULL;
    SDL_Rect posGame;
    char st[MAX_SIZE_FILE_NAME];

    int time_pause=*time;

    gameOver = imageLoad("sprites/game-over.jpg");
    posGame.x = posGame.y = 0;
    SDL_SetAlpha(gameOver, SDL_SRCALPHA, 200);
    SDL_BlitSurface(gameOver,NULL,screen,&posGame);
    SDL_Rect posTex;
    posTex.x = 394;
    posTex.y = 180;

    printText(screen,&posTex,"PAUSE",186,38,18,"polices/manga.ttf",65,1);
    posTex.x = 295;
    posTex.y = 260;
    sprintf(st,"Press %s to restart",SDL_GetKeyName(kc[3]));
    printText(screen,&posTex,st,186,38,18,"polices/ubuntu.ttf",50,1);
    SDL_Flip(screen);
    in->key[kc[3]] = 0;

    while(!in->key[kc[3]] && *go)
    {

        updateWaitEvents(in,go);
        if(in->quit)
            *go = 0;

    }
    SDL_FreeSurface(gameOver);

    *time=time_pause;
    in->key[kc[3]] = 0;
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
    sprintf(charLife,"%d",player->life);
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
