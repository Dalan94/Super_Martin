/*!
 * \file    file_level.c
 * \brief   map file gestion
 * \author  Remi BERTHO
 * \date    15/03/14
 * \version 1.0
 */

 #include "file_level.h"


Level *openLevel(char *file_name,list *l,platformSet *ps)
 {
    FILE *ptr_file;
    int i,j;
    char buffer[BUFFER_SIZE];
    Level *lvl;
    char *cleaning;

    SDL_Rect vert[MAX_NB_PLATFORM], horiz[MAX_NB_PLATFORM];
    SDL_Rect mark;

    if ((lvl=(Level *)malloc(sizeof(Level))) == NULL)
    {
            printf("\nProbleme allocation memoire\n");
            perror("");
            exit(0);
    }

    ptr_file=openFile(file_name,"r");

    if (ptr_file == NULL)
    {
        printf("\nErreur : Le fichier n'a pas pu etre lu.\n");
        return NULL;
    }

    fscanf(ptr_file,"%d",&(lvl->width));
    fscanf(ptr_file,"%d",&(lvl->height));
    fscanf(ptr_file,"%d",&(lvl->timer_level));

    initLevel(lvl);

    fgets(buffer,BUFFER_SIZE,ptr_file);
    fgets(lvl->tileSet,MAX_SIZE_FILE_NAME,ptr_file);
    fgets(lvl->background,MAX_SIZE_FILE_NAME,ptr_file);
    fgets(lvl->music,MAX_SIZE_FILE_NAME,ptr_file);

    /*  Cleaning the strings    */
     cleaning = strchr(lvl->tileSet, '\n');
        *cleaning = 0;

     cleaning = strchr(lvl->background, '\n');
        *cleaning = 0;

     cleaning = strchr(lvl->music, '\n');
        *cleaning = 0;

    for(i = 0 ; i<MAX_NB_PLATFORM ; i++)
    {
        vert[i].x = vert[i].y = horiz[i].x = horiz[i].y = -1;
    }

    for(i=0 ; i < lvl->height ; i++)
    {
        fgets((char *)lvl->map[i],lvl->width+1,ptr_file);
        fgets(buffer,BUFFER_SIZE,ptr_file);
        for (j=0 ; j < lvl->width ; j++)
        {
            switch(lvl->map[i][j])
            {
                case 'E':
                    createEnemy("sprites/Characters/witch_doctor.png",j*TILE_SIZE,(i-1)*TILE_SIZE,l,1);
                    lvl->map[i][j] = VOID;
                    break;
                case 'A':
                    mark.y = i*TILE_SIZE;
                    mark.x = j*TILE_SIZE;
                    platformMap(ps,vert,mark,1);
                    lvl->map[i][j] = VOID;
                    break;
                case 'B':
                    mark.y = i*TILE_SIZE;
                    mark.x = j*TILE_SIZE;
                    platformMap(ps,horiz,mark,0);
                    lvl->map[i][j] = VOID;
                    break;
                case 'C':
                    lvl->map[i][j] = HAMMER;
                    break;

                case 'F': // left rocket
                    lvl->map[i][j] = CANON_L;
                    createEnemy(NULL,j*TILE_SIZE,(i-1)*TILE_SIZE,l,2);
                    break;
                case 'G': // right rocket
                    lvl->map[i][j] = CANON_R;
                    createEnemy(NULL,j*TILE_SIZE,(i-1)*TILE_SIZE,l,3);
                    break;

                case 'D':
                    lvl->map[i][j] = CANON_B;
                    createEnemy(NULL,j*TILE_SIZE,(i-1)*TILE_SIZE,l,4);
                    break;

                default:
                    if(lvl->map[i][j] < 65)
                        lvl->map[i][j]-= 48;
            }
        }
    }
    lvl->tileSetUse = 0;

     closeFile(ptr_file);



     return lvl;
 }


void closeLevel(Level *lvl)
{
    int i;

    for (i=0 ; i<lvl->height ; i++)
        free(lvl->map[i]);

    free(lvl->map);
}


Level *initLevel(Level *lvl)
{
    int i;

    if ((lvl->map=(unsigned char **)malloc(lvl->height*sizeof(unsigned char*))) == NULL)
    {
        fprintf(stderr,"\nalloction memory error\n");
        perror("");
        exit(0);
    }

    for (i=0 ; i<lvl->height ; i++)
    {
        if ((lvl->map[i]=(unsigned char *)malloc(lvl->width*sizeof(unsigned char)+1)) == NULL)
        {
            fprintf(stderr,"\nalloction memory error\n");
            perror("");
            exit(0);
        }
    }

    return lvl;
}


char **readLevelFile(char *file_path, int *nb_lvl)
{
    char **level_names;
    FILE *ptr_file;
    int i;

    ptr_file=openFile(file_path,"r");
    if (ptr_file == NULL)
     {
        fprintf(stderr,"\nError : couldn't read the file.\n");
        return NULL;
     }

    fscanf(ptr_file,"%d",nb_lvl);

    if ((level_names=(char **)malloc(*nb_lvl*sizeof(char*))) == NULL)
    {
        fprintf(stderr,"\nalloction memory error\n");
        perror("");
        exit(0);
    }

    for (i=0 ; i<*nb_lvl ; i++)
    {
        if ((level_names[i]=(char *)malloc(MAX_SIZE_FILE_NAME*sizeof(char))) == NULL)
        {
            fprintf(stderr,"\nalloction memory error\n");
            perror("");
            exit(0);
        }
    }

    for (i=0 ; i<*nb_lvl ; i++)
    {
        fscanf(ptr_file,"%s",level_names[i]);
    }

    closeFile(ptr_file);

    return level_names;
}


void closeLevelList(char **level_names, int nb_lvl)
{
    int i;
    for (i=0 ; i<nb_lvl ; i++)
        free(level_names[i]);
    free(level_names);
}
