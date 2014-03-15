/*!
 * \file    file_map.c
 * \brief   Gestion des fichiers de carte
 * \author  Remi BERTHO
 * \date    15/03/14
 * \version 1.0
 */

 #include "file_level.h"

/*!
 * \fn  Level *openMap(char *file_name, Level *lvl)
 *  Ouvre un fichier map, et le stocke
 * \param[in] file_name le nom du fichier
 * \param[out] lvl le niveau
 * \return un pointeur sur le niveau
 */
Level *openMap(char *file_name, Level *lvl)
 {
     FILE *ptr_file;
     int i;
     char string_width[TAILLE_MAX_NB_BLOCS_LARGEUR];
     char string_height[TAILLE_MAX_NB_BLOCS_HAUTEUR];
     char buffer[TAILLE_BUFFER];

     ptr_file=openFile(file_name,"r");

     if (ptr_file == NULL)
     {
        printf("\nErreur : Le fichier n'a pas pu etre lu.\n");
        return NULL;
     }

     fgets(string_width,TAILLE_MAX_NB_BLOCS_LARGEUR,ptr_file);
     sscanf(string_width,"%d",&(lvl->width));
     fgets(string_height,TAILLE_MAX_NB_BLOCS_HAUTEUR,ptr_file);
     sscanf(string_height,"%d",&(lvl->height));

     initLevel(lvl);

    for(i=0 ; i < lvl->height ; i++)
    {
        fgets((char *)lvl->map[i],lvl->width+1,ptr_file);
        fgets(buffer,TAILLE_BUFFER,ptr_file);
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
    int i;
    FILE *ptr_file;

    ptr_file=openFile(file_name,"w");

    fprintf(ptr_file,"%d\n",lvl->width);
    fprintf(ptr_file,"%d\n",lvl->height);

    for (i=0 ; i<lvl->height ; i++)
        fprintf(ptr_file,"%s\n",lvl->map[i]);

    closeFile(ptr_file);
}
