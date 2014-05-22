/*!
 * \file    file.h
 * \brief   Prototypes des fonctions d'acces aux fichiers
 * \author  Remi BERTHO
 * \date    15/03/14
 */

#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*!
 * \fn FILE *openFile(char name[], char mode[])
 *  open a file
 * \param[in] name the file name/path
 * \param[in] mode the opening mode
 * \return a pointer on the opened file, NULL if error
 */
FILE *openFile(char name[], char mode[]);

/*!
 * \fn int closeFile(FILE *ptr_file)
 *  close a file
 * \param[in] *ptr_file the file to be closed
 * \return int 0 if the file was succefuly closed, 1 if not
 */
int closeFile(FILE *ptr_fichier);


#endif
