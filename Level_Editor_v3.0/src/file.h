/*!
 * \file    file.h
 * \brief   file.c header
 * \author  Remi BERTHO, Glenn HERROU
 * \date    2014-05-12
 */

#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*!
 * \fn FILE *openFile(char name[], char mode[])
 *  Open a file which path is name with the given mode
 * \param[in] name[] name of the file
 * \param[in] mode[] the opening mode
 * \return a pointer if the opening has been succesfull, NULL otherwise
 */

FILE *openFile(char nome[], char mode[]);

/*!
 * \fn int closeFile(FILE *ptr_file)
 *  Close the given file
 * \param[in] *ptr_file the file
 * \return 0 if the file has been succesfully closed, 1 otherwise
 */

int closeFile(FILE *ptr_fichier);

#endif
