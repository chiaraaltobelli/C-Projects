#ifndef CHRCATS_H
#define CHRCATS_H

#include "chrcat.h"

typedef void *Chrcats;

extern Chrcat newChrcats(Chrcat chrList, char *name, char *characters);
extern char* getCharacters(Chrcat chrList, int k);
extern void countMatches(Chrcat chrList, char* userInput);
extern char *charToString(char* s);
extern void printStrings(Chrcat chrList);
extern void printToFile(Chrcat chrList, int fd,char* msg);
extern void freeChrcats(Chrcat chrList);

#endif
