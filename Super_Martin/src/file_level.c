/*!
 * \file    file_map.c
 * \brief   Gestion des fichiers de carte
 * \author  Remi BERTHO
 * \date    15/03/14
 * \version 1.0
 */

 #include "file_level.h"

/*!
 * \fn  Level *openLevel(char *file_name)
 *  Ouvre un fichier map, et le stocke
 * \param[in] file_name le nom du fichier
 * \return un pointeur sur le niveau
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

     fgets(buffer,TAILLE_BUFFER,ptr_file);
     fgets(lvl->background,TAILLE_MAX_NOM_FICHIER,ptr_file);
     fgets(lvl->music,TAILLE_MAX_NOM_FICHIER,ptr_file);

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
 *  Ferme un niveau
 * \param[out] lvl le niveau
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
 *  Initialise un niveau en supposant que sa largeur et sa hauteur sont deja dans le niveau
 * \param[out] lvl le niveau
 * \return un pointeur sur le niveau
 */
Level *initLevel(Level *lvl)
{
    int i;

    if ((lvl->map=(unsigned char **)malloc(lvl->height*sizeof(unsigned char*))) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    for (i=0 ; i<lvl->height ; i++)
    {
        if ((lvl->map[i]=(unsigned char *)malloc(lvl->width*sizeof(unsigned char)+1)) == NULL)
        {
            printf("\nProbleme allocation memoire\n");
            perror("");
            exit(0);
        }
    }

    return lvl;
}

/*!
 * \fn  void writeLevel(char *file_name, Level *lvl)
 *  Ecrit le niveau dans un fichier
 * \param[in] lvl le niveau
 * \param[in] file_name le nom du fichier
 */
void writeLevel(char *file_name, Level *lvl)
{
    int i,j;
    FILE *ptr_file;

    ptr_file=openFile(file_name,"w");

    fprintf(ptr_file,"%d\n",lvl->width);
    fprintf(ptr_file,"%d\n",lvl->height);
    fprintf(ptr_file,"%s\n",lvl->background);

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
 *  Lis le fichier level
 * \param[out] nb_lvl le nombre de niveau
 * \return un pointeur sur la liste des niveaux cree
 */
char **readLevelFile(int *nb_lvl)
{
    char **level_names;
    FILE *ptr_file;
    int i;

    ptr_file=openFile("level/level","r");
    if (ptr_file == NULL)
     {
        printf("\nErreur : Le fichier n'a pas pu etre lu.\n");
        return NULL;
     }

    fscanf(ptr_file,"%d",nb_lvl);

    if ((level_names=(char **)malloc(*nb_lvl*sizeof(char*))) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    for (i=0 ; i<*nb_lvl ; i++)
    {
        if ((level_names[i]=(char *)malloc(TAILLE_MAX_NOM_FICHIER*sizeof(char))) == NULL)
        {
            printf("\nProbleme allocation memoire\n");
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
 *  Desalloue la liste des noms de niveau
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