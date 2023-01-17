#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //file control options
#include<string.h> 
#include <unistd.h>
#include "chrcat.h"
#include "ChrCats.h"
#include "utilities.h"
#include "list.h"
#include "error.h"

//Create list for Chrcats
extern Chrcat newChrcats(Chrcat chrList, char *name, char *characters) {
  List aList = chrList;  
  Chrcat r = newChrcat(name, characters);
  aList = cons(r,aList);
  return (Chrcat)aList; //confirm this is what is supposed to be returned
}

//Return just the characters for a Chrcat
extern char* getCharacters(Chrcat chrList, int k) {
  Chrcat r = car(chrList);
  List myList = cdr(chrList);
  for(int i = 0; i != k; i ++){
      r = car(myList); //first elem in list
      myList = cdr(myList); //next elem in list
  }
  return r->characters;
}

//Count instances of match between userInput and characters
extern void countMatches(Chrcat chrList, char* userInput){
  char *s; //hold characters for Chrcat
  Chrcat r = car(chrList);
  List myList = cdr(chrList);
  while (myList != NULL){
    s = r->getCharacter(r);
    r->count = r->count + r->countMatch(userInput, s);
    r = car(myList); //first elem in list
    myList = cdr(myList); //next elem in list
  }
    s = r->getCharacter(r);
    r->count = r->count + r->countMatch(userInput, s);
}

//Print character as string
extern char *charToString(char* s) {
  char *ts;
  asprintf(&ts,"%s", s);
  return ts;
}

// Print Chrcats to string
extern void printStrings(Chrcat chrList){
   List p = chrList;
    while(p!=NULL){
      Chrcat r = car(p);
      r->printString(r);
      p= cdr(p);
    }
}

//Print list to output file
extern void printToFile(Chrcat chrList, int fd, char* msg){
    List p = chrList;
    int fwrite;
    if(msg != NULL){
      if((fwrite = write(fd, msg, getLength(msg))) == -1){
        ERROR("Could not write to file.");
      }
    }
    while(p!=NULL){
      Chrcat r = car(p);
      char *s=r->chrcatToString(r);
      fwrite = write(fd, s, getLength(s));
      if(fwrite == -1){
        ERROR("Could not write to file.");
      }
      write(fd,"\n",1);
      p= cdr(p);
      free(s);
    }
}

//Free chrcatsRep
extern void freeChrcats(Chrcat chrList) {
  freedata(chrList);
}
