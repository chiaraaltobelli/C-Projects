#ifndef CHRCAT_H
#define CHRCAT_H

#include "error.h"

extern int getSize();
extern void newChrcat(char *name, char *characters);
extern char* getCharacters(int k);
extern void countMatch(char* userInput, char* s, int k);
extern void printString();
extern void freeChrcatRep();

#endif
