/*!
 * \file    file_level.c
 * \brief   Management of the level files
 * \author  Remi BERTHO, Glenn HERROU
 * \date    2014-05-12
 * \version 2.0
 */

 #include "file_level.h"

Level *openLevel(char *file_name)
 {
     FILE *ptr_file;
     int i,j;
     char buffer[BUFFER_SIZE];
     Level *lvl;
     char *cleaning;

     if ((lvl=(Level *)malloc(sizeof(Level))) == NULL)
     {
            printf("\nError allocating memory\n");
            perror("");
            exit(0);
     }

     ptr_file=openFile(file_name,"r");

     if (ptr_file == NULL)
     {
        printf("\nError opening the file\n");
        return NULL;
     }

     fscanf(ptr_file,"%d",&(lvl->width));
     fscanf(ptr_file,"%d",&(lvl->height));
     fscanf(ptr_file,"%d",&(lvl->timer_level));

     initLevel(lvl);

     fgets(buffer,BUFFER_SIZE,ptr_file);
     fgets(lvl->tileSet,MAX_LENGTH_FILE_NAME,ptr_file);
     fgets(lvl->background,MAX_LENGTH_FILE_NAME,ptr_file);
     fgets(lvl->music,MAX_LENGTH_FILE_NAME,ptr_file);

    /*  Cleaning the strings    */
     cleaning = strchr(lvl->tileSet, '\n');
        *cleaning = 0;

     cleaning = strchr(lvl->background, '\n');
        *cleaning = 0;

     cleaning = strchr(lvl->music, '\n');
        *cleaning = 0;

    for(i=0 ; i < lvl->height ; i++)
    {
        fgets((char *)lvl->map[i],lvl->width+1,ptr_file);
        fgets(buffer,BUFFER_SIZE,ptr_file);
        for (j=0 ; j < lvl->width ; j++)
        {
            if(lvl->map[i][j] < 65)
                lvl->map[i][j]-=48;
        }
    }

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
        printf("\nError allocating memory\n");
        perror("");
        exit(0);
    }

    for (i=0 ; i<lvl->height ; i++)
    {
        if ((lvl->map[i]=(unsigned char *)malloc(lvl->width*sizeof(unsigned char)+1)) == NULL)
        {
            printf("\nError allocating memory\n");
            perror("");
            exit(0);
        }
    }

    return lvl;
}

void writeLevel(char *file_name, Level *lvl)
{
    int i,j;
    FILE *ptr_file;

    Level *adapt = adaptSizeLevel(lvl);

    ptr_file=openFile(file_name,"w");

    fprintf(ptr_file,"%d\n",adapt->width);
    fprintf(ptr_file,"%d\n",adapt->height);
    fprintf(ptr_file,"%d\n",adapt->timer_level);
    fprintf(ptr_file,"%s\n",adapt->tileSet);
    fprintf(ptr_file,"%s\n",adapt->background);
    fprintf(ptr_file,"%s\n",adapt->music);

    for (i=0 ; i<adapt->height ; i++)
    {
        for (j=0 ; j<adapt->width ; j++)
        {
            if(adapt->map[i][j] < 65)
            {
                fprintf(ptr_file,"%hhu",adapt->map[i][j]);
            }
            else
            {
                fprintf(ptr_file,"%c",adapt->map[i][j]);
            }
        }

        fprintf(ptr_file,"\n");
    }
    closeLevel(adapt);
    closeFile(ptr_file);
}

char **readLevelFile(int *nb_lvl)
{
    char **level_names;
    FILE *ptr_file;
    int i;

    ptr_file=openFile("../Super_Martin/level/level","r");
    if (ptr_file == NULL)
     {
        fprintf(stderr, "\nError opening the file\n");
        return NULL;
     }

    fscanf(ptr_file,"%d",nb_lvl);

    if ((level_names=(char **)malloc(*nb_lvl*sizeof(char*))) == NULL)
    {
        fprintf(stderr, "\nError allocating memory\n");
        perror("");
        exit(0);
    }

    for (i=0 ; i<*nb_lvl ; i++)
    {
        if ((level_names[i]=(char *)malloc(MAX_LENGTH_FILE_NAME*sizeof(char))) == NULL)
        {
            fprintf(stderr, "\nError allocating memory\n");
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

Level *adaptSizeLevel(Level *lvl)
{
    int end;
    int i,j;
    Level *adapt_lvl;

    if ((adapt_lvl=(Level *)malloc(sizeof(Level))) == NULL)
     {
            fprintf(stderr, "\nError allocating memory\n");
            perror("");
            exit(0);
     }

    end = searchEndLevel(lvl);
    adapt_lvl->height=lvl->height;
    adapt_lvl->width = end;
    strcpy(adapt_lvl->music,lvl->music);
    adapt_lvl->timer_level=end/5;
    strcpy(adapt_lvl->background,lvl->background);
    strcpy(adapt_lvl->tileSet,lvl->tileSet);
    initLevel(adapt_lvl);

    for(i=0 ; i< end; i++)
    {
        for (j=0 ; j<adapt_lvl->height ; j++)
            adapt_lvl->map[j][i]=lvl->map[j][i];
    }

    return adapt_lvl;
}

int searchEndLevel(Level *lvl)
{
    int i;
    int j;

    for (i=lvl->width ; i>0 ; i--)
    {
        for (j=0 ; j<lvl->height ; j++)
        {
            if (lvl->map[j][i-1] != 0)
                return i;
        }
    }
    return 0;
}
