/*!
 * \file    file_level.h
 * \brief   Gestion des fichiers de carte
 * \author  Remi BERTHO
 * \date    15/03/14
 * \version 1.0
 */

#ifndef FILE_MAP_H_INCLUDED
#define FILE_MAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "const.h"
#include "structures.h"
#include "enemies.h"

#define TAILLE_MAX_NB_BLOCS_LARGEUR 5
#define TAILLE_MAX_NB_BLOCS_HAUTEUR 4
#define TAILLE_BUFFER 2

Level *openLevel(char *file_name,list *l);
void closeLevel(Level *lvl);
Level *initLevel(Level *lvl);
void writeLevel(char *file_name, Level *lvl);
char **readLevelFile(int *nb_lvl);
void closeLevelList(char **level_names, int nb_lvl);

#endif // FILE_MAP_H_INCLUDED
