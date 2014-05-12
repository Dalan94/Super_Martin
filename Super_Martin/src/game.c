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
 *\return 1 if the maryo dies, 0 if he wins or if he quits the level
 */



int play(SDL_Surface *screen, char *level_name,Sound *sound_sys,int *go,SDLKey *kc, Input *in, Player *player, char player_name[MAX_SIZE_FILE_NAME], int currentLevel, int nb_lvl)
{
    SDL_TimerID timer = NULL, timer1 = NULL;

    int previous_time=0;
    int current_time=0;
    int old_time=201;
    int pause=0;
    int ret = 0;
    int launch = 1;

    int acceleration=0;
    float speed=0;


    /*définition du niveau*/
    Map *m;

    /*définition du joueur*/
    Character *maryo;
    list maryoList;

    /*définition des ennemis*/
    list enemyList;

    /*définition des plateformes*/
    platformSet ps;

    /* projectile set declaration */
    projectileSet pjs;

    /*définition des surfaces*/
    SDL_Surface *background = NULL;
    SDL_Rect posBack;


    /*Gestion des mouvements*/
    float move_right=0;
    float move_left=0;
    int jump = 0;

    memset(in->key,0,sizeof(char)*SDLK_LAST);
    if(in->isJoystick)
        initInput(in);

    if(!in->useJoystick)
        SDL_JoystickEventState(SDL_IGNORE);

    if(player->nbLifes < 0)
        loadPlayer("save/.save", player_name, player);
    /*gestion des inputs*/

    //effacer l'écran
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    posBack.x=0;
    posBack.y = 0;


    /*initialisation des ennemis*/
    initList(&enemyList);

    /*initialisation des plateformes */
    initPlatformSet(&ps);

    /* projectile set initialization */
    initProjSet(&pjs);

    /*initialisation de la carte et du niveau*/
    m = initMap(screen,level_name,&enemyList,&ps);

    /*Gestion de la musique*/
    playMusic(m->lvl->music,sound_sys);

    /*Démarrage du timer */
    timer=SDL_AddTimer(1000,decomptage,&(m->lvl->timer_level));
    timer=SDL_AddTimer(5000,rocketLaunch,&launch);

    /*chargement de l'arrière plan*/
    background = imageLoadAlpha(m->lvl->background);

    /*initialisation du joueur*/

    maryo = createCharacter("sprites/Characters/maryo.png",5*TILE_SIZE,8*TILE_SIZE-39,0, player->nbProjectile, player->nbCoins, player->nbLifes);
    initList(&maryoList);
    maryoList.current = maryoList.first = maryoList.last = newNode(maryo,NULL,NULL);

    SDL_EnableKeyRepeat(100,100); //répétition des touches

    current_time=previous_time=SDL_GetTicks();

    while(!in->key[SDLK_ESCAPE] && *go && !in->isJoystick|!in->button[BACK])
    {

        /* récupération des inputs clavier et gestion de leurs auctions*/

        updateEvents(in,go);
        inputActionGame(in,&move_left,&move_right,&jump,&pause,maryo,&acceleration,kc,&pjs);

        if(in->quit)
            *go = 0;

        /* gestion de la mort*/
        if((maryo->location.y+maryo->tile->h/NB_TILE_MARYO_HEIGHT) >= m->lvl->height*TILE_SIZE-1)
            maryo->hp = 0;
        if (old_time != m->lvl->timer_level || !maryo->hp)
        {
            if(!(m->lvl->timer_level>0 && maryo->hp))
            {
                stopSound(sound_sys,1);
                player->nbLifes--;
                printGameOver(screen,go,in,sound_sys);
                if(player->nbLifes >= 0)
                    ret = 1;

                else
                    ret = 0;
                break;
            }
            old_time=m->lvl->timer_level;
            m->lvl->tileSetUse ^= 1;
        }

        if(maryo->isHurt>0)
            maryo->isHurt--;
        else
            maryo->isHurt = 0;


        if((maryo->location.x)/TILE_SIZE >= m->lvl->width - IMG_END_SIZE / TILE_SIZE + 1 && *go)
        {
            player->nbProjectile = maryo->nbProjectile;
            player->nbLifes = maryo->nbLifes;
            if(player->levelMax == currentLevel)
            {
                player->nbCoins = maryo->countStars;
                if(player->levelMax < (nb_lvl))
                    player->levelMax += 1;
                savePlayer("save/.save", player_name, player);
            }

            printWin(screen,go,in,sound_sys);
            break;
        }

        if (pause)
        {
            printPause(screen,in,&(m->lvl->timer_level),go,kc);
            pause=0;
        }

            /* update the game objects position */
        movePlatform(maryo,&ps,&enemyList);
        updateSpeed(&speed,acceleration);
        move(move_left,move_right,jump,maryo,m,&speed,&acceleration,&enemyList,sound_sys,&ps);
        moveProjectiles(maryo,m,&pjs,&enemyList);
        moveEnemies(&enemyList,m,&maryoList,&pjs,&launch);
            /* ******************************** */

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //effacer l'écran

            /* print all the game components */
        SDL_BlitSurface(background,NULL,screen,&posBack); // blit du background

        updateScreenMap(screen,m, m->lvl->tileSet); //blit du niveau

                /* game objets */
        blitPlatform(screen,&ps,m);
        blitCharacter(screen,maryo,m);
        blitProjectile(screen,&pjs,m);
        blitEnnemies(screen,&enemyList,m);
                /* ******** */

        printHUD(screen,maryo,m); //HUD
            /* ******************************* */

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

    free((void *)maryo);
    freeEnemies(&enemyList);
    freeEnemies(&maryoList);
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
void move(float move_left, float move_right,int jump, Character *player,Map *m,float *speed, int *acceleration,list *l,Sound *sound_sys,platformSet *ps)
{
    int ret = moveCharacter(player,move_left,move_right,jump,m,speed,l,sound_sys,ps);
    if (move_right && !move_left)
    {
        (*acceleration)++;

        {

            if (player->location.x - m->xScroll > m->screenWidth*(50-DEPLACEMENT_POURCENTAGE)/100  && player->location.x - m->xScroll < m->screenWidth*(50 + MARGE_SCROLLING-DEPLACEMENT_POURCENTAGE)/100)
                scrolling(m,RIGHT,*speed);
            else if (player->location.x - m->xScroll >= m->screenWidth*(50 + MARGE_SCROLLING-DEPLACEMENT_POURCENTAGE)/100 )
                scrolling(m,RIGHT,2*(*speed));
        }
    }
    if (move_left && !move_right)
    {
        (*acceleration)++;

        {

            if (player->location.x - m->xScroll < m->screenWidth*(50+DEPLACEMENT_POURCENTAGE)/100 && player->location.x - m->xScroll > m->screenWidth*(50 - MARGE_SCROLLING+DEPLACEMENT_POURCENTAGE)/100)
                scrolling(m,LEFT,*speed);
            else if (player->location.x - m->xScroll <= m->screenWidth*(50- MARGE_SCROLLING+DEPLACEMENT_POURCENTAGE)/100)
                scrolling(m,LEFT,2*(*speed));
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
    //posTex.x = 394;
    posTex.x = -1;
    posTex.y = screen->h/2 - 100;

    printText(screen,&posTex,"PAUSE",186,38,18,"polices/manga.ttf",65,1);
    posTex.x = -1;
    posTex.y = screen->h/2 + 100;
    sprintf(st,"Press %s to restart",SDL_GetKeyName(kc[3]));
    printText(screen,&posTex,st,186,38,18,"polices/ubuntu.ttf",50,1);
    SDL_Flip(screen);


    in->key[kc[3]] = 0;
    if(in->isJoystick)
        in->button[START] = 0;

    while(!(in->key[kc[3]] || in->isJoystick&in->button[START]) && *go)
    {

        updateWaitEvents(in,go);
        if(in->quit)
            *go = 0;

    }
    SDL_FreeSurface(gameOver);

    *time=time_pause;
    if(in->isJoystick)
        in->button[START] = 0;
    in->key[kc[3]] = 0;
}

Uint32 decomptage(Uint32 intervalle,void* parametre)
{
    int *time = parametre;
    (*time)--;
    return intervalle;
}

Uint32 rocketLaunch(Uint32 intervalle,void* parametre)
{
    int *launch = parametre;
    *launch ^= 1;
//    if(*launch)
//        return 1;
    return 5000;
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
    char charLife[2];
    char charHp[5];
    SDL_Surface *heart = NULL;
    SDL_Rect posHeart = {screen->w-105,10,0,0},posHP = {screen->w-70,10,0,0}, posLife = {screen->w-130,10,0,0};

    /*stars gestion*/
    char charCountStars[5];
    SDL_Surface *stars = NULL;
    SDL_Rect posStars ={screen->w/2,3,0,0}, posCountStars ={screen->w/2+40,10,0,0};

    /*time gestion*/
    char charTime[5];
    SDL_Rect posTime={40,10,0,0};
    SDL_Surface *watch;
    SDL_Rect posWatch = {10,10,0,0};

    /* hammer gestion */
    char charCountHammer[5];
    SDL_Surface *hammer = NULL;
    SDL_Rect posHam = {10,screen->h-50,0,0}, posCountHam = {50,screen->h-50,0,0};

    /*sprites loading*/
    heart = imageLoadAlpha("sprites/Heart.png");
    watch = imageLoadAlpha("sprites/watch.png");
    stars = imageLoadAlpha("sprites/stars.png");
    hammer = imageLoadAlpha("sprites/ico_hammer.png");
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

    if(hammer == NULL)
    {
        perror("error while loading hammer sprite");
        exit(errno);
    }


    /*affichage temps*/
    sprintf(charTime,"%d",m->lvl->timer_level);
    printText(screen,&posTime,charTime,0,0,0,"polices/code.otf",20,0);
    SDL_BlitSurface(watch,NULL,screen,&posWatch);
    /* ***** */

    /*affichage de la vie*/
    sprintf(charLife,"%d",player->nbLifes);
    printText(screen,&posLife,charLife,255,100,100,"polices/code.otf",20,1);
    sprintf(charHp,"%d",player->hp);
    printText(screen,&posHP,charHp,255,100,100,"polices/code.otf",20,1);
    SDL_BlitSurface(heart,NULL,screen,&posHeart);

    /*affichage du nombre d'étoiles récoltées*/
    sprintf(charCountStars,"%d",player->countStars);
    printText(screen,&posCountStars,charCountStars,0,0,0,"polices/code.otf",20,1);
    SDL_BlitSurface(stars,NULL,screen,&posStars);

    /* print hammer */
    sprintf(charCountHammer,"%d",player->nbProjectile);
    printText(screen,&posCountHam,charCountHammer,0,0,0,"polices/code.otf",40,1);
    SDL_BlitSurface(hammer,NULL,screen,&posHam);

    SDL_FreeSurface(heart);
    SDL_FreeSurface(watch);
    SDL_FreeSurface(stars);
    SDL_FreeSurface(hammer);

}
