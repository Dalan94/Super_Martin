/*!
 * \file game.c
 * \brief contient les fonction liées au jeu
 * \author Xavier COPONET
 * \date 2014-02-27
 */



#include "game.h"


int play(SDL_Surface *screen, char *level_name,Sound *sound_sys,int *go,SDLKey *kc, Input *in, Player *player, char player_name[MAX_SIZE_FILE_NAME], int currentLevel, int nb_lvl)
{
    SDL_TimerID timer = NULL;

    int previous_time=0;
    int current_time=0;
    int old_time=201;
    int pause=0;
    int ret = 0;
    int launch = 1;

    int acceleration=0;
    float speed=0;


    /*level definition*/
    Map *m;

    /*player definition*/
    Character *maryo;
    list maryoList;

    /*enemies definition*/
    list enemyList;

    /*platforms definition*/
    platformSet ps;

    /* projectile set declaration */
    projectileSet pjs;

    /*surfaces definition */
    SDL_Surface *background = NULL;
    SDL_Rect posBack;


    /*movement gestion*/
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
    /*nputs input*/

    //clear screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    posBack.x=0;
    posBack.y = 0;


    /*enemies initalization*/
    initList(&enemyList);

    /*platform initalization */
    initPlatformSet(&ps);

    /* projectile set initialization */
    initProjSet(&pjs);

    /*initialisation de la carte et du niveau*/
    m = initMap(screen,level_name,&enemyList,&ps);

    /*music gestion*/
    playMusic(m->lvl->music,sound_sys);

    /*timers starting */
    timer=SDL_AddTimer(1000,decrement,&(m->lvl->timer_level));
    timer=SDL_AddTimer(FRENQUENCY_ROCKET_LAUNCH,rocketLaunch,&launch);

    /*background loading*/
    background = imageLoadAlpha(m->lvl->background);

    /*player initalization*/

    maryo = createCharacter("sprites/Characters/maryo.png",5*TILE_SIZE,8*TILE_SIZE-39,0, player->nbProjectile, player->nbCoins, player->nbLifes);
    initList(&maryoList);
    maryoList.current = maryoList.first = maryoList.last = newNode(maryo,NULL,NULL);

    SDL_EnableKeyRepeat(100,100); //key repetition

    current_time=previous_time=SDL_GetTicks();

    while(!in->key[SDLK_ESCAPE] && *go && (!in->isJoystick||!in->button[BACK]))
    {

        /* player inputs gestion*/

        updateEvents(in,go);
        inputActionGame(in,&move_left,&move_right,&jump,&pause,maryo,&acceleration,kc,&pjs);

        if(in->quit)
            *go = 0;

        /* death gestion*/
        if((maryo->location.y+maryo->tile->h/NB_TILE_MARYO_HEIGHT) >= m->lvl->height*TILE_SIZE-1)
            maryo->hp = 0;

        if (old_time != m->lvl->timer_level || !maryo->hp)
        {
            if(!(m->lvl->timer_level>0 && maryo->hp>0))
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

        /* player imunity to damage gestion */
        if(maryo->isHurt>0)
            maryo->isHurt--;
        else
            maryo->isHurt = 0;


        /* level end and saving player stats gestion */
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

        /* pause gstion */
        if (pause)
        {
            printPause(screen,in,&(m->lvl->timer_level),go,kc);
            pause=0;
        }

            /* update the game objects position */
        movePlatform(maryo,&ps,&enemyList,m);
        updateSpeed(&speed,acceleration);
        move(move_left,move_right,jump,maryo,m,&speed,&acceleration,&enemyList,sound_sys,&ps);
        moveProjectiles(maryo,m,&pjs,&enemyList);
        moveEnemies(&enemyList,m,&maryoList,&pjs,&launch);
            /* ******************************** */

        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255)); //clean screen

            /* print all the game components */
        SDL_BlitSurface(background,NULL,screen,&posBack); // background blit

        updateScreenMap(screen,m, m->lvl->tileSet); //level blit

                /* game objets blit*/
        blitPlatform(screen,&ps,m);
        blitCharacter(screen,maryo,m);
        blitProjectile(screen,&pjs,m);
        blitEnemies(screen,&enemyList,m);
                /* ******** */

        printHUD(screen,maryo,m); // print HUD
            /* ******************************* */

        waitFPS(&previous_time,&current_time); //fps

        SDL_Flip(screen);//screen flipping
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

    SDL_Delay(1500);  //pause to avoid to quit the screen immediatly if the player uses a key when he dies

    while(!updateWaitEvents(in,go));
    if(in->quit)
        *go = 0;
    SDL_FreeSurface(gameOver);
    stopSound(sound_sys,1);

}



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

    SDL_Delay(1500); //pause to avoid to quit the screen immediatly if the player uses a key when he wins

    while(!updateWaitEvents(in,go));
    if(in->quit)
        *go = 0;
    SDL_FreeSurface(win);
    stopSound(sound_sys,1);
}


void move(float move_left, float move_right,int jump, Character *player,Map *m,float *speed, int *acceleration,list *l,Sound *sound_sys,platformSet *ps)
{
    moveCharacter(player,move_left,move_right,jump,m,speed,l,sound_sys,ps);
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

    while(!(in->key[kc[3]] || (in->isJoystick&&in->button[START])) && *go)
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


Uint32 decrement(Uint32 interval,void* parameter)
{
    int *time = parameter;
    (*time)--;
    return interval;
}

Uint32 rocketLaunch(Uint32 intervalle,void* parametre)
{
    int *launch = parametre;
    *launch ^= 1;

    return intervalle;
}

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
