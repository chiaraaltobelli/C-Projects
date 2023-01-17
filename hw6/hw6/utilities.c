#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

//Function to get user input
extern char *getInput(int *len) 
{
  char* line=0;
  size_t n=0;
  // ssize_t len;
  *len=getline(&line,&n,stdin);
  if (len>=0) {
    if (line[*len-1]=='\n')
      line[*len-1]=0;
    if (*len==1){
      len = 0; //if user hits enter, set len to 0
    }
    return line;
  }
  free(line);
  return 0;
}

//Return error on malloc failure
extern void mallocError(char *s) {
  fprintf(stderr,"error: %s\n",s);
  exit(1);
}

//Determine the length of a string
extern int getLength(char *c)
{
  int i = 0;
  char *temp = c;
  while (temp[i] != '\0'){ //confirm not null
    i++;
  }
  return i;
}

//Convert character to lowercase value
extern void toLower(char *c) {
    if (*c >= 'A' && *c <= 'Z'){
      *c -= 'A'-'a';
    }
}