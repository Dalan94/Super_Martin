/*!
 * \file    file.c
 * \brief   Fonctions d'acces au fichiers
 * \author  Remi BERTHO
 * \date    15/03/14
 */

 #include "file.h"


/*!
 * \fn FILE *openFile(char nom[], char mode[])
 *  Ouvre un fichier a partir de son nom (nom[]) et du mode voulu (mode[])
 * \param[in] nom[] le nom du fichier
 * \param[in] mode[] le mode voulu
 * \return un pointeur sur le fichier ouvert, NULL s'il y a eut un probleme
 */
FILE *openFile(char nom[], char mode[])
{
    FILE *ptr_fichier;

    if ((ptr_fichier=fopen(nom,mode)) == (FILE *) NULL )
    {
        printf("\nErreur lors de l'ouverture du fichier %s\n",nom);
        perror("");
    }
    return ptr_fichier;
}

/*!
 * \fn int closeFile(FILE *ptr_fichier)
 *  Ferme le fichier
 * \param[in] *ptr_fichier le fichier
 * \return entier 0 si tout s'est bien passe, 1 sinon
 */
int closeFile(FILE *ptr_fichier)
{
    int i;

    i=fclose(ptr_fichier);
    if (i)
    {
        printf("Erreur lors de la fermeture du fichier");
        perror("");
    }

    return i;
}

/*!
 * \fn int readFileSize(FILE *ptr_fichier)
 *  Lis la taille du fichier
 * \param[in] *ptr_fichier le fichier
 * \return entier ayant la taille du fichier
 */
int readFileSize(FILE *ptr_fichier)
{
    int taille;
    int position=ftell(ptr_fichier);

    fseek(ptr_fichier,0,SEEK_END);
    taille=ftell(ptr_fichier);
    fseek(ptr_fichier,position,SEEK_SET);

    return taille;
}

