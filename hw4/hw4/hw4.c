//Compile: gcc -o hw4 hw4.c -g -Wall
//Execute: ./hw4
//Debug: gdb ./hw4

#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "chrcat.h"

int main(int argc, char* argv[]) { 
    // Create built in categories
    newChrcat("Lower_Vowels","aeiou");
    newChrcat("Lowercase_Consonants","bcdfghjklmnpqrstvwxyz");
    newChrcat("Letters","^abcdefghijklmnopqrstuvwxyz");
    newChrcat("Punctuation","-.'\"'?^!");

    //Add category information to chrcats struct
    int numCat = getSize(); //get number of categories in chrcatsRep
    if(argc > 1 && argc %2 == 1){//check that even number of arguments has been entered
        for (int i = 1; i < argc; i++){
            newChrcat(argv[i], argv[i+1]);
            i++;//add extra count to move to next pair
            numCat++;//increase chrcats array
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

    // Get user input fom command line for comparison to characters
    while(1){
        int len = 0; //get length of user input
        printf("Please enter a string (ctrl-d or enter to stop):\n");
        char *userInput = getInput(&len); //get input from user
        // printf("len is: %d\n",len);
        if (len <= 1){
            free(userInput);
            break;
        } else{
            //Test user input against categories
            char* s; //get category characters
            for (int k = 0; k < numCat; k ++){
                s= getCharacters(k);//assign characters to s
                countMatch(userInput, s, k);//compare user input to characters
             }
        }
        //Free user entered input
        free(userInput);
    }

    //Print chrcatsRep
    printString();

    //Free ChrcatRep
    freeChrcatRep();

  return 0;
}

