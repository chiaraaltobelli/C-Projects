#include <stdio.h>
#include <stdlib.h>
#include "chrcat.h"
#include "utilities.h"

//Create rep struct that is not visible from main
typedef struct {
  char *name;
  char *characters;
  int count;
} ChrcatRep;

//Initialize chrcatsRep with no categories
typedef ChrcatRep *ChrCatsRep;
static ChrCatsRep chrcatsRep=0;

//Private methods
static char *chrcatToString(int i);
static char caseFolding(char userInput, int *j);
static int rangeTest(char *s,char catChar, int j);

//Global variables
int size = 0; //number of categories in chrcatsRep
int availMem = 0;//available memory in chrcatsRep
int len = 0; //length of characters for each chrcatsRep category

//Return number of categories in chrcatsRep
extern int getSize(){
  return size;
}

//Constructor - call newChrcatRep to get memory from malloc and add user entered category to chrcatsRep
extern void newChrcat(char *name, char *characters) {
  ChrcatRep *r=(ChrcatRep*)malloc(sizeof(ChrcatRep));
  if(!r)
    mallocError("malloc() failed");
  r->name=name;
  r->characters=characters;
  r->count = 0;
  //Check if more memory needs to be allocated
  if(size == 0){
    chrcatsRep = (ChrcatRep*)malloc(sizeof(ChrcatRep)); //allocate enough memory for first category
    availMem++;//add one spot for available memory
  }
  if(size == availMem){
    availMem = size*2;//double available memory
    chrcatsRep = (ChrcatRep*)realloc(chrcatsRep,(availMem)* sizeof(ChrcatRep));//reallocate memory for chrcatsRep
  } 
  chrcatsRep[size] = *r;//add r to chrcatsRep
  size++;//increase size to new number of categories in chrcatsRep
  free(r);
}

//Returns just the characters for an index (k) of chrcatsRep
extern char* getCharacters(int k) {
  return chrcatsRep[k].characters;
}

//Count instances of match between userInput and chrcatsRep characters
extern void countMatch(char* userInput, char* s, int k){
  len = getLength(s);//get length of character category
  for(int j = 0; s[j] != '\0'; j ++){
    char catChar = s[j]; //assign category character to separate var in case it needs to be converted to lower
    int flag = 0; //range test flag
    char beg, end;//hold 1st and last chars for ranges
    //Loop through each character in userinput
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
            chrcatsRep[k].count++;
          }
      } else {
        if(userChar == catChar){
          chrcatsRep[k].count++;
        }
      }
    }
  }
}

// Print chrcatsRep to string
extern void printString(){
  char* string = "";
  for (int n =0; n  < size; n++)
  {
    string = chrcatToString(n);
    printf("%s\n",string);
    free(string);
  }
}

//Convert chrcatsRep to string  
static char *chrcatToString(int i) {
  char *ts;
  asprintf(&ts,"%s (%s): %d",chrcatsRep[i].name, chrcatsRep[i].characters, chrcatsRep[i].count);
  return ts;
}

//Free chrcatsRep
extern void freeChrcatRep() {
  free(chrcatsRep);
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