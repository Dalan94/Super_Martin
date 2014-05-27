/*!
 * \file    file.c
 * \brief   file access functions
 * \author  Remi BERTHO
 * \date    15/03/14
 */

 #include "file.h"



FILE *openFile(char name[], char mode[])
{
    FILE *ptr_fichier;

    if ((ptr_fichier=fopen(name,mode)) == (FILE *) NULL )
    {
        fprintf(stderr,"error while opening file %s : ",name);
        perror("");

    }
    return ptr_fichier;
}


int closeFile(FILE *ptr_file)
{
    int i;

    i=fclose(ptr_file);
    if (i)
    {
        fprintf(stderr,"error while closing file");
        perror("");
    }

    return i;
}


