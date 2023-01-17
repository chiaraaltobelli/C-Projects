#include <stdio.h>
#include <stdlib.h>
#include "ChrCat3.h"

int main(int argc, char* argv[]) {
  // Create built in categories
  chrcats[0] = newChrcat("Lower_Vowels","aeiou");
  chrcats[1] = newChrcat("Lowercase_Consonants","bcdfghjklmnpqrstvwxyz");
  chrcats[2] = newChrcat("Letters","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

  //Determine number of non-null elements in in chrcats[]
  int count = countCat();

  int j = count; //copy count value to use for while loop to keep adding user categories

  //Determine number of categories entered by user
  int allowedArgs = (MAXCATS * 2)-(count*2) +1; //total args should be 1 for name and 1 for characters per MAXCAT, plus 1 to run program
  // printf("allowedArgs is: %d, argc is: %d\n",allowedArgs, argc);
  if(argc > 1 && argc %2 == 1)//check that even number of arguments has been entered
  {
    if(argc>allowedArgs)
    {
      WARN("You have entered too many arguments, only the max allowed have been added.\n");
      for (int i = 1; j < MAXCATS; i++)
      {
        chrcats[j] = newChrcat(argv[i], argv[i+1]);
        i++;//add extra count to move to next pair
        j++;//increase chrcats array
      }
    }
    if (argc<=allowedArgs)
    {
      for (int i = 1; i < argc; i++)
      {
        chrcats[j] = newChrcat(argv[i], argv[i+1]);
        i++;//add extra count to move to next pair
        j++;//increase chrcats array
      }
    }
  }
  else{
    ERROR("Invalid amount of arguments entered.");
  }

  // Get user input for comparison
  printf("Please enter a string: \n");
  ssize_t userLength = 0; //length of user string
  char *getInput = getstr(&userLength); //get input from user

  //count up each instance of match between user entered data and category data
  testCategories(getInput, userLength);  

  //Free pointers
  free(getInput);

  return 0;
}
