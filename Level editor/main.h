#include "structs.h"


extern void init(char*);
extern void cleanup(void);
extern void getInput(void);
extern void draw(void);
extern void loadGame(void);
extern void delay(unsigned int frameLimit);
extern void update(void);


Input input;
Gestion jeu;
Map map;
Cursor cursor;
