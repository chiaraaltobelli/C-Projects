#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "ChrCats.h"
#include "error.h"

int main(int argc, char* argv[]) { 
    //Create containers for lists
    Chrcats cc1=0; //built in categories
    Chrcats cc2=0; //user added categories
    int argsPerChrcat = 2; //expected number of arguments per category added

    //Create built in categories
    cc1 = newChrcats(cc1,"Lower_Vowels","aeiou");
    cc1 = newChrcats(cc1,"Lowercase_Consonants","bcdfghjklmnpqrstvwxyz");
    cc1 = newChrcats(cc1,"Letters","^abcdefghijklmnopqrstuvwxyz");
    cc1 = newChrcats(cc1,"Punctuation","-.'\"'?^!");

    //Get user created categories
    if(argc > 1 && argc %argsPerChrcat == 1){//check that correct number of arguments have been entered
        for (int i = 1; i < argc; i++){
            cc2=newChrcats(cc2, argv[i], argv[i+1]);
            i++;//add extra count to move to next pair
        }
    }
    else {
        if(argc==1){
            ERROR("No arguments entered.");
        } 
        else{
            ERROR("Invalid amount of arguments entered.");
        }
    }

    //Get user input fom command line for comparison to characters
    while(1){
        int len = 0; //get length of user input
        printf("Please enter a string (ctrl-d or enter to stop):\n");
        char *userInput = getInput(&len); //get input from user
        if (len <= 1){
            free(userInput);
            break;
        } else{
            countMatches(cc1, userInput);//compare user input to characters
            countMatches(cc2, userInput);//compare user input to characters
        }
        //Free user entered input
        free(userInput);
    }

    //Print data
    printf("Built in categories:\n");
    printStrings(cc1);
    printf("\nUser categories:\n");
    printStrings(cc2);

    //Free Chrcat
    freeChrcats(cc1);
    freeChrcats(cc2);

  return 0;
}

