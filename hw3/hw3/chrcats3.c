#include <stdio.h>
#include <stdlib.h>
#include "ChrCat3.h"

//Create rep struct that is not visible from main
typedef struct {
  char *name;
  char *characters;
} *ChrcatRep;

//Create Chrcatrep to hold private struct that is not visible from main
typedef ChrcatRep ChrCatsRep[MAXCATS+1];
ChrCatsRep chrcatsRep;

static void addToChrcatsRep(ChrcatRep r);
static void categoryLength(int j, int *length);
static void totalMatch(char getInput,int i, int j, int myNum[]);
static char *chrcatToString(int i);
static void rangeTest();
static void caseTest();
static void mallocError(char *s);

//Create function that is called from main to test all categories
void testCategories(char *getInput, ssize_t len)
{
  //Array to hold counts for each category
  int myNum[MAXCATS];
  for (int i = 0; chrcatsRep[i] != NULL; i ++)
  {
    myNum[i] = 0;
  }

  int length = 0; //length of element in chrcatsRep array

  //Check for ranges within array
  rangeTest();

  // Check for case sensitivity
  caseTest();
  
  //Count number of matches for each category
  for (int j = 0; chrcatsRep[j] != NULL; j ++)
  {
    categoryLength(j, &length); //count length of each array category
    for (int i = 0; i < length; i++)
    {
      for (int k = 0; k < len; k ++){
        totalMatch(getInput[k], i, j, myNum); //count number of matches for each category
      }
    }
  }
  // Print totals for each category
  char* string = "";
  for (int n =0; chrcatsRep[n] != NULL; n++)
  {
    string = chrcatToString(n);
    printf("\n%s\n",string);
    printf("Totals are: %d\n", myNum[n]);
    free(string);
  }

  //Free chrcats - note this does not fail on Onyx but is failing here?
  // for(int c = 0; chrcatsRep[c]; c ++)
  // {
  //   freeChrcat(chrcatsRep[c]);
  // }
}

//Determine the length of each category array element
static void categoryLength(int j, int *length)
{
  int i = 0;
  char *temp = chrcatsRep[j]->characters; //hold char from array
  while (temp[i] != '\0'){ //confirm not null
    i++;
  }
  *length = i; //increase count to determine length
}

//Count total matches between user data and category array element
static void totalMatch(char getInput,int i, int j, int myNum[])
{
  if(getInput==chrcatsRep[j]->characters[i])
  {
    ++myNum[j];
  }
}

//Test for ranges
static void rangeTest(){
  int begChar = 0; //hold first character in range
  int endChar = 0; //hold last character in range
  int charLength = 0; //get length of chrcatsRep.characters

  //Loop through each category type
  for (int i = 0; chrcatsRep[i] != NULL; i++)
  {
    int flag = 0; //use flag to test if range detected
    int charCount = 0;//hold number of characters in each character category, restart at new category
    char tempString[BUFFER]; //hold expanded range
    for (int j = 0; chrcatsRep[i]->characters[j] != '\0'; j++)
    {
      categoryLength(i, &charLength); //get length of character category
      if (chrcatsRep[i]->characters[j] != '-')//Store all characters except -
      {
        tempString[charCount] = chrcatsRep[i]->characters[j];
        charCount++;
      }
      if(chrcatsRep[i]->characters[j] == '-') //if dash found, check not first or last character
      {
        if((j == 0) || (j == charLength-1))
        {
          break; //end if - is found as first or last character
        }
        else
        {
          flag = 1; 
          begChar = chrcatsRep[i]->characters[j-1]; //get the first character in the range
          endChar = chrcatsRep[i]->characters[j+1]; //get the last character in the range
          int  arrSize = endChar-begChar; //determine the size of the range
          char charArray[arrSize+1]; //array to add each character in the range
          for(int k = 1; k < arrSize; k++) //add additional characters in range to array
          {
            charArray[k-1] = (char)begChar + k; //start k at 1 to increment from beginning character
            tempString[charCount] = charArray[k-1];//k-1 is 0 - assign to tempstring from charArray[0]
            charCount++;
          }
        }
      }
    }
    if(flag==1) //only override chrcatsRep[i].characters if range is found
      {
      {
        int n;
        for (n = 0; tempString[n] != '\0'; n ++)
        {
          chrcatsRep[i]->characters[n] = tempString[n];
        }
        chrcatsRep[i]->characters[n]=0; //set last character to 0
      }
      //clear out array
      for (int k = 0; tempString[k+1] != '\0'; k ++)
      {
        tempString[k] = 0;
      }      
    }
  }
}

//Test for case
static void caseTest()
{
int len = 0; //get length of chrcatsRep.characters

  //Test each character category
  for (int i = 0; chrcatsRep[i] != NULL; i++)
  {
    char tempString[BUFFER];
    int charCount = 0;//hold number of characters in each character category, restart at new category
    categoryLength(i, &len); //get length of character category
    if(chrcatsRep[i]->characters[0] == '^') //if ^ found, continue converting case
    {
      int  arrSize = 0; //determine the size of the range
      for (int j = 0; j < len; j ++)
      {
        if (chrcatsRep[i]->characters[j] >= 'a' && chrcatsRep[i]->characters[j] <= 'z')
        {
          arrSize = arrSize+2;//add two to array size for every lowercase letter found
        }
        else
        {
          arrSize++; //add one to array size if character is not a lowercase letter
        }
      }

    char charArray[arrSize]; //array to add each character in the range
    int index = 0;
    for(int k = 1; k <= arrSize; k++) //add additional characters in range to array
    {
      if (chrcatsRep[i]->characters[k] >= 'a' && chrcatsRep[i]->characters[k] <= 'z')
      {
        charArray[index] = (char)chrcatsRep[i]->characters[k]; //skipping ^ symbol, add characters to new array
        charArray[index +1] = (char)chrcatsRep[i]->characters[k] - 32; //convert to upper case
        index = index + 2;
      }
      else if (index < arrSize)
      {
        charArray[index] = (char)chrcatsRep[i]->characters[k];
        index = index + 1;
      }
    }
    for (int n = 0; n <index; n++)
    {
      tempString[n] = charArray[n];
      charCount++;
    }
      int n;
      for (n = 0; tempString[n] != '\0'; n ++)
        {
          chrcatsRep[i]->characters[n] = tempString[n];
        }
      chrcatsRep[i]->characters[n]=0;

      for (int k = 0; tempString[k+1] != '\0'; k ++)
      {
        tempString[k] = 0;
      }
    }
  }
}

//Return error on failure
static void mallocError(char *s) {
  fprintf(stderr,"error: %s\n",s);
  exit(1);
}

//Create new ChrcatRep r and allocate memory
static ChrcatRep newChrcatRep() {
  ChrcatRep r=(ChrcatRep)malloc(sizeof(*r));
  if (!r)
    mallocError("malloc() failed");
  return r;
}

//Constructor - call newChrcatRep to get memory from malloc and add user entered category to
//chrcatsRep that is not visible from main
extern Chrcat newChrcat(char *name, char *characters) {
  ChrcatRep r=newChrcatRep();
  r->name=name;
  r->characters=characters;
  addToChrcatsRep(r);
  return (Chrcat)r; //return void pointer so client cannot access the members
}

//Add categories received from main to ChrcatRep that is not visible to client 
static void addToChrcatsRep(ChrcatRep r)
{
  //Determine number of non-null elements in array
  int count = countCat();
  chrcatsRep[count] = r;
}

//Free memory
extern void freeChrcat(Chrcat s) {
  ChrcatRep r=(ChrcatRep)s;
  free(r->name);
  free(r->characters);
  free(r);
}

//Convert to string  
static char *chrcatToString(int i) {
  char *ts;
  asprintf(&ts,"%s (%s)",chrcatsRep[i]->name, chrcatsRep[i]->characters);
  return ts;
}

//Get user input
extern char *getstr(ssize_t *len) 
{
  char *line=0;
  size_t n=0;
  *len=getline(&line,&n,stdin);
  if (len>=0) {
    if (line[*len-1]=='\n')
      line[*len-1]=0;
    if (*len==1){
      *len = 0; //if user hits enter, set len to 0
    }
    return line;
  }
  free(line);
  return 0;
}

//Count number of categories
extern int countCat()
{
  int count = 0;
  for (int i = 0; chrcats[i] != NULL; i++){
    count ++;
  }
  return count;
}
