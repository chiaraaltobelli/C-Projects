#ifndef CHRCAT_H
#define CHRCAT_H
#define MAXCATS 10
#define BUFFER 1000 //buffer to account for user entered categories

#include "error.h"

typedef void *Chrcat;

typedef Chrcat ChrCats[MAXCATS+1];
ChrCats chrcats;

void testCategories(char *getInput, ssize_t len);
extern Chrcat newChrcat(char *name, char *characters);
extern void freeChrcat(Chrcat s);
extern char *getstr(ssize_t *len);
extern int countCat(); 
// extern char *chrcatToString(Chrcat s);

#endif
