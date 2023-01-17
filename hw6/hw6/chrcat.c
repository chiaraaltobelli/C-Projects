#include <stdio.h>
#include <stdlib.h>

#include "chrcat.h"
#include "utilities.h"
#include "error.h"


//Global variables
int len = 0; //length of characters for each chrcatsRep category

//Returns characters for a given Chrcat
static char* getCharacter(Chrcat s) {
  return s->characters;
}

//Case folding
static char caseFolding(char userInput, int *j){
  toLower(&userInput);
  if(*j==0){
    ++*j;//do not include ^ in match count
  }
  return userInput;
}

// Check for range
static int rangeTest(char* s, char catChar, int j){
  int flag = 0;
  if(catChar == '-'){
    if((s[0] != '-') && (s[len-1] != '-')){
      flag = 1;
    }
  }
  return flag;
}

//Count instances of match between userInput and chrcatsRep characters
extern int countMatch(char* userInput, char* s){
  int count = 0; 
  len = getLength(s);//get length of character category
  for(int j = 0; s[j] != '\0'; j ++){
    char catChar = s[j]; //assign category character to separate var in case it needs to be converted to lower
    int flag = 0; //range test flag
    char beg, end;//hold 1st and last chars for ranges
    //Loop through each character in userinput
    if(userInput[0] == '\0'){
      break; //use for arrays with uninitialized values
    }
    else{
      for(int i = 0; userInput[i] != '\0'; i++){
        //Check for case folding
        char userChar = userInput[i];//assign character to separate var in case it needs to be converted to lower
        if(s[0] =='^'){
          userChar = caseFolding(userInput[i],&j);
          catChar = s[j];//update value of catChar to next character (skip ^)
          toLower(&catChar);//convert catChar to lower for comparison
        }
        //Check for range
        flag = rangeTest(s, catChar, j);
        if(flag==1){
            beg = s[j-1];
            end = s[j+1];
            if(userChar > beg && userChar < end){
              count++;
            }
        } else {
          if(userChar == catChar){
            count++;
          }
        }
      }
    }
  }
  return count;
}

extern char *chrcatToString(Chrcat s) {
  char *ts;
  asprintf(&ts,"%s [%s]: %d",s->name,s->characters,s->count);
  return ts;
}

// Print Chrcats to string
static void printString(Chrcat s){
  char *ts=s->chrcatToString(s); //turns to string to print it
  printf("%s\n",ts);
  free(ts);
}

//Create new Chrcat
extern Chrcat newChrcat(char *name, char *characters) {
  Chrcat r=(Chrcat)malloc(sizeof(*r));
  if (!r)
    mallocError("malloc() failed");
  else{
    r->name=name;
    r->characters=characters;
    r->count=0;
    r->getCharacter = getCharacter;
    r->countMatch = countMatch;
    r->printString = printString;
    r->chrcatToString = chrcatToString;
  }
  return r;
}

extern void freeChrcat(Chrcat s) {
  free(s);
}