/*!
 * \file    file_level.h
 * \brief   Header of file_level.c
 * \author  Remi BERTHO
 * \date    15/03/14
 * \version 1.0
 */

#ifndef FILE_LEVEL_H_INCLUDED
#define FILE_LEVEL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "const.h"

#define TAILLE_BUFFER 2

Level *openLevel(char *file_name);
void closeLevel(Level *lvl);
Level *initLevel(Level *lvl);
void writeLevel(char *file_name, Level *lvl);
char **readLevelFile(int *nb_lvl);
void closeLevelList(char **level_names, int nb_lvl);

#endif // FILE_LEVEL_H_INCLUDED
