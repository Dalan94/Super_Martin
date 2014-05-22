/*!
 * \file    file_level.h
 * \brief   file_level.c header
 * \author  Remi BERTHO, Glenn HERROU
 * \date    2014-05-12
 * \version 2.0
 */

#ifndef FILE_MAP_H_INCLUDED
#define FILE_MAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "const.h"
#include "structures.h"

#define TAILLE_MAX_NB_BLOCS_LARGEUR 5
#define TAILLE_MAX_NB_BLOCS_HAUTEUR 4
#define BUFFER_SIZE 2

/*!
 * \fn  Level *openLevel(char *file_name)
 *  Open a level file and store the level corresponding to the file
 * \param[in] file_name the name of the level file
 * \return a pointer to the level created
 */

Level *openLevel(char *file_name);

/*!
 * \fn  void closeLevel(Level *lvl)
 *  Close a level by freeing its allocated memory
 * \param[out] lvl The level
 */

void closeLevel(Level *lvl);

/*!
 * \fn  Level *initLevel(Level *lvl)
 *  Initialize a level. The width and the Height of the level must be stored in the level before calling this function.
 * \param[out] lvl The level
 * \return a pointer on the level initialized
 */

Level *initLevel(Level *lvl);

/*!
 * \fn  void writeLevel(char *file_name, Level *lvl)
 *  Write the given level in the given file
 * \param[in] lvl the file
 * \param[in] file_name the name of the file
 */

void writeLevel(char *file_name, Level *lvl);

/*!
 * \fn  char **readLevelFile(int *nb_lvl)
 *  Read the file including the list of existing levels
 * \param[out] nb_lvl the number of level in the file
 * \return a pointer to an array of strings containing the list of the levels
 */

char **readLevelFile(int *nb_lvl);

/*!
 * \fn  void closeLevelList(char **level_names, int nb_lvl)
 *  Free the array containing the list of the levels
 * \param[in,out] level_names the list of existing levels
 * \param[in] nb_lvl the number of existing levels
 */

void closeLevelList(char **level_names, int nb_lvl);

/*!
 * \fn  Level *adaptSizeLevel(Level *lvl)
 *  Adapt the width of a level
 * \param[in,out] lvl the level to adapt
 */

Level *adaptSizeLevel(Level *lvl);

/*!
 * \fn  int searchEndLevel(Level *lvl)
 *  Search the end of a level
 * \param[in,out] lvl the level
 */

int searchEndLevel(Level *lvl);

#endif // FILE_MAP_H_INCLUDED
