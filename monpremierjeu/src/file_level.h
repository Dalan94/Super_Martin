/*!
 * \file    file_map.h
 * \brief   Gestion des fichiers de carte
 * \author  Remi BERTHO
 * \date    15/03/14
 * \version 1.0
 */

#ifndef FILE_MAP_H_INCLUDED
#define FILE_MAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "const.h"

#define TAILLE_MAX_NB_BLOCS_LARGEUR 5
#define TAILLE_MAX_NB_BLOCS_HAUTEUR 4
#define TAILLE_BUFFER 2

Level *openMap(char *file_name, Level *lvl);
void closeLevel(Level *lvl);
Level *initLevel(Level *lvl);
void writeLevel(char *file_name, Level *lvl);

#endif // FILE_MAP_H_INCLUDED
