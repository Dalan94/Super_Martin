/*!
 * \file    file_map.c
 * \brief   Management of level specific files
 * \author  Remi BERTHO, Glenn HERROU
 * \date    15/03/14
 * \version 1.0
 */

 #include "file_level.h"

/*!
 * \fn  Level *openLevel(char *file_name)
 *  Open a level file and create the level corresponding to the file
 * \param[in] file_name The name of the file to open
 * \return a pointer on the level created
 */

Level *openLevel(char *file_name)
 {
     FILE *ptr_file;
     int i,j;
     char buffer[TAILLE_BUFFER];
     Level *lvl;
     char *saut_ligne;

     if ((lvl=(Level *)malloc(sizeof(Level))) == NULL)
     {
            printf("\nError allocating memory\n");
            perror("");
            exit(0);
     }

     ptr_file=openFile(file_name,"r");

     if (ptr_file == NULL)
     {
        printf("\nError opening file %s\n", file_name);
        return NULL;
     }

     fscanf(ptr_file,"%d",&(lvl->width));
     fscanf(ptr_file,"%d",&(lvl->height));
     fscanf(ptr_file,"%d",&(lvl->timer_level));

     initLevel(lvl);

     fgets(buffer,TAILLE_BUFFER,ptr_file);
     fgets(lvl->background,MAX_LENGTH_FILE_NAME,ptr_file);
     fgets(lvl->music,MAX_LENGTH_FILE_NAME,ptr_file);

     /*Enleve le saut de ligne final de background*/
     saut_ligne = strchr(lvl->background, '\n');
        *saut_ligne = 0;

    /*Enleve le saut de ligne final de sound*/
     saut_ligne = strchr(lvl->music, '\n');
        *saut_ligne = 0;

    for(i=0 ; i < lvl->height ; i++)
    {
        fgets((char *)lvl->map[i],lvl->width+1,ptr_file);
        fgets(buffer,TAILLE_BUFFER,ptr_file);
        for (j=0 ; j < lvl->width ; j++)
            lvl->map[i][j]-=48;
    }

     closeFile(ptr_file);
     return lvl;
 }

/*!
 * \fn  void closeLevel(Level *lvl)
 *  Close a level by deallocating its map
 * \param[out] lvl The level to close
 */
void closeLevel(Level *lvl)
{
    int i;

    for (i=0 ; i<lvl->height ; i++)
        free(lvl->map[i]);

    free(lvl->map);
}

/*!
 * \fn  Level *initLevel(Level *lvl)
 *  Initialize a level. The width and the height of the level must be initiated before calling this function
 * \param[out] lvl The level to initialize
 * \return a pointer on the level initialized
 */
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

/*!
 * \fn  void writeLevel(char *file_name, Level *lvl)
 *  Write a level in a file
 * \param[in] lvl The level to write
 * \param[in] file_name The file to write in
 */
void writeLevel(char *file_name, Level *lvl)
{
    int i,j;
    FILE *ptr_file;
    ptr_file=openFile(file_name,"w+");

    fprintf(ptr_file,"%d\n",lvl->width);
    fprintf(ptr_file,"%d\n",lvl->height);
    fprintf(ptr_file,"%d\n",lvl->timer_level);
    fprintf(ptr_file,"%s\n",lvl->background);
    fprintf(ptr_file,"%s\n",lvl->music);

    for (i=0 ; i<lvl->height ; i++)
    {
        for (j=0 ; j<lvl->width ; j++)
            fprintf(ptr_file,"%hhu",lvl->map[i][j]);
        fprintf(ptr_file,"\n");
    }
    closeFile(ptr_file);
}

/*!
 * \fn  char **readLevelFile(int *nb_lvl)
 *  Read the file "level" which contains the list of all existing levels. The first line of this file contains the length of the list, each other line contains one, and only one, level file name
 * \param[out] nb_lvl The number of existing levels
 * \return a pointer on the array containing  all existing level names
 */
char **readLevelFile(int *nb_lvl)
{
    char **level_names;
    char *tmp;
    FILE *ptr_file;
    int i;

    ptr_file=openFile("/home/glenn/GIT/Super_Martin/Super_Martin/level/level","r");
    if (ptr_file == NULL)
     {
        printf("\nError opening file 'level/level'\n");
        return NULL;
     }

    fscanf(ptr_file,"%d",nb_lvl);

    if ((level_names=(char **)malloc(*nb_lvl*sizeof(char*))) == NULL)
    {
        printf("\nError allocating memory\n");
        perror("");
        exit(0);
    }

    for (i=0 ; i<*nb_lvl ; i++)
    {
        if ((level_names[i]=(char *)malloc(MAX_LENGTH_FILE_NAME*sizeof(char))) == NULL)
        {
            printf("\nError allocating memory\n");
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

/*!
 * \fn  void closeLevelList(char **level_names, int nb_lvl)
 *  Deallocate the array of level names created by the function readLevelFile
 * \param[in,out] level_names la liste des noms de niveau
 * \param[in] nb_lvl le nombre de niveau
 */
void closeLevelList(char **level_names, int nb_lvl)
{
    int i;
    for (i=0 ; i<nb_lvl ; i++)
        free(level_names[i]);
    free(level_names);
}
