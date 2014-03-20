/*!
* \file input.h
 * \brief Header of input.c
 * \author Glenn HERROU
 * \date 2014-03-18
 */

#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "const.h"

void getInput(Input *input);
void update(Map *m, Input *input, Cursor *cursor);

extern Input input;
extern Map map;
extern Cursor cursor;





#endif // INPUT_H
