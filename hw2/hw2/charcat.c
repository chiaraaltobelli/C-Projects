//Compile: gcc -o charcat charcat.c sq.c -g -Wall
//Execute: ./charcat
//Debug: gdb ./charcat

#include <stdio.h>
#include <stdlib.h>
#include "ChrCat.h"


//Struct of character pointer ChrCat
typedef struct{
  char *name; //category name (ie vowels)
  char *characters; //characters within each category
} ChrCat;

//Characters to test against
typedef ChrCat ChrCats[];
static ChrCats chrcats =
{
  {"Vowels", "aeiouAEIOU"}, //vowels
  {"Consonants", "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ"}, //consonants
  {"Lower", "abcdefghijklmnopqrstuvqxyz"}, //lower case
  {"Upper", "ABCDEFGHIJKLMNOPQRSTUVQXYZ"}, //upper case
  {"Digits", "0123456789"},//digits
  {"Letter", "abcdefghijklmnopqrstuvqxyzABCDEFGHIJKLMNOPQRSTUVQXYZ"}, //letters
  {"Punctuation", "!,.?;:/'"}, //punctuation
  {"Ascender", "bdfhiklt"}, //ascenders
  {"Descender", "gjqpy"}, //descenders
  {"Curvy","aceghjmnosuBCDGJOQSU"}, //curvy
  {"Sticky", "bdfhiklpqrtvwxyzAEFHIKLMNPRTVWXYZ"} //sticky
};

static void categoryLength(int j, int *length);
static void totalMatch(char getInput,int i, int j, int myNum[]);
static char *chrcatToString(int i);

void testCategories(char *getInput, ssize_t len)
{
  //array to hold counts for each category
  int myNum[SIZE];
  for (int i = 0; i < SIZE; i ++)
  {
    myNum[i] = 0;
  }

  int length = 0; //length of element in chrcats array

  //count number of matches for each category
  for (int j = 0; j < SIZE; j ++){
    categoryLength(j, &length); //count length of each category array
    for (int i = 0; i < length; i++)
    {
      for (int k = 0; k < len; k ++){
        totalMatch(getInput[k], i, j, myNum); //count number of matches for each category
      }
    }
  }

  //Print totals for each category
  char* string = "";
  for (int n =0; n < SIZE; n++)
  {
    string = chrcatToString(n);
    printf("\n%s\n", string);
    printf("Total count: %d\n", myNum[n]);
    free(string);
  }
}

//Determine the length of each category array element
static void categoryLength(int j, int *length)
{
  char *temp = chrcats[j].characters; //hold char from array
  int i = 0;
  while (temp[i] != '\0'){ //confirm not null
    i++;
  }
  *length = i; //increase count to determine length
}

//Count total matches between user data and category array element
static void totalMatch(char getInput,int i, int j, int myNum[])
{
  if(getInput==chrcats[j].characters[i])
  {
    ++myNum[j];
  }
}

//Convert to string  
static char *chrcatToString(int i) {
  char *ts;
  asprintf(&ts,"%s (%s)",chrcats[i].name, chrcats[i].characters);
  return ts;
}

