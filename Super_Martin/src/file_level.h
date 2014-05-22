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
#include "mobile_platform.h"

#define TAILLE_MAX_NB_BLOCS_LARGEUR 5
#define TAILLE_MAX_NB_BLOCS_HAUTEUR 4
#define TAILLE_BUFFER 2

/*!
 * \fn  Level *openLevel(char *file_name, list *l,platformSet *ps)
 * Open a map file and stock the map and the enemies
 * \param[in] file_name the map file name
 * \param[out] l the enemy list to stock the enemies.
 * \param[out] ps the platform set for mobile platforms
 * \return a pointer on the level structure
 */
Level *openLevel(char *file_name,list *l,platformSet *ps);

/*!
 * \fn  void closeLevel(Level *lvl)
 *  close a level freeing its allocated memory
 * \param[out] lvl the level to be closed
 */
void closeLevel(Level *lvl);

/*!
 * \fn  Level *initLevel(Level *lvl)
 *  Initialize a level assuming its width and height fields are already set
 * \param[out] lvl the level
 * \return a pointer on the level structure
*/
Level *initLevel(Level *lvl);

/*!
 * \fn  char **readLevelFile(int *nb_lvl)
 *  read a file level
 * \param[out] nb_lvl number of level
 * \return pointer on the level list created
 */
char **readLevelFile(char *file_path, int *nb_lvl);

/*!
 * \fn  void closeLevelList(char **level_names, int nb_lvl)
 *  desallocate the level name list
 * \param[in,out] level_names level name list
 * \param[in] nb_lvl number of level
 */
void closeLevelList(char **level_names, int nb_lvl);

#endif // FILE_MAP_H_INCLUDED
