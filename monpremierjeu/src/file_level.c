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

     initLevel(lvl);

     fgets(buffer,TAILLE_BUFFER,ptr_file);
     fgets(lvl->background,TAILLE_MAX_NOM_FICHIER,ptr_file);

     /*Enleve le saut de ligne final de background*/
     saut_ligne = strchr(lvl->background, '\n');
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
    fprintf(ptr_file,"%s",lvl->background);

    for (i=0 ; i<lvl->height ; i++)
    {
        for (j=0 ; j<lvl->width ; j++)
            fprintf(ptr_file,"%hhu",lvl->map[i][j]);
        fprintf(ptr_file,"\n");
    }

    closeFile(ptr_file);
}
