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

FILE *openFile(char nome[], char mode[]);
int closeFile(FILE *ptr_fichier);
int readFileSize(FILE *ptr_fichier);

#endif
