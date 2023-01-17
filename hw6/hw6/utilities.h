#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>

//Function to get user input
extern char *getInput(int *len);

//Return error on malloc failure
extern void mallocError(char *s);

//Determine the length of a string
extern int getLength(char *c);

//Convert character to lowercase value
extern void toLower(char *c) ;

#endif