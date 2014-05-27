/*!
 * \file    file.c
 * \brief   Functions to access to the files
 * \author  Remi BERTHO, Glenn HERROU
 * \date    2014-05-12
 */

 #include "file.h"

FILE *openFile(char name[], char mode[])
{
    FILE *ptr_file;

    if ((ptr_file=fopen(name,mode)) == (FILE *) NULL )
    {
        fprintf(stderr,"\nError while opening the file %s\n",name);
        perror("");
    }
    return ptr_file;
}

int closeFile(FILE *ptr_file)
{
    int i;

    i=fclose(ptr_file);
    if (i)
    {
        fprintf(stderr, "Error while closing file");
        perror("");
    }

    return i;
}

