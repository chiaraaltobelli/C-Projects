#ifndef CHRCAT_H
#define CHRCAT_H

typedef struct Chrcat{
  char *name;
  char *characters;
  int count;
  char* (*getCharacter)(struct Chrcat* s); //get characters for the chrcat
  int (*countMatch)(char* userInput, char* s); //count matches between characters and user input
  void (*printString)(struct Chrcat* s); //print chrcats
} *Chrcat;

extern Chrcat newChrcat(char *name, char *characters);
extern void freeChrcat(Chrcat s);

#endif
