#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //file control options
#include <unistd.h>
#include <string.h>
#include "utilities.h"
#include "ChrCats.h"
#include "error.h"


int main(int argc, char* argv[]) { 
    
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("PROGRAM DESCRIPTION:\n");
    printf("This program takes input and compares it to built-in and user entered categories, returning a count of matching characters.\n");
    printf("Format used: ./hw6 <input file> <output file> <category1> <characters> <category2> <characters>...\n");
    printf("The character '-' can be substituted for input or output file name to take input from or output to the command line instead.\n");
    printf("Format to input and output to command line: ./hw6 - - <category1> <characters> <category2> <characters>...\n");
    WARN("Project contains built in categories: lowercase vowels, lowercase consonants, upper & lower letters, and punctuation.");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------\n");

    //Create containers for lists
    Chrcats cc1=0; //built in categories
    Chrcats cc2=0; //user added categories
    int argsPerChrcat = 2; //expected number of arguments per category added

    //Create built in categories
    cc1 = newChrcats(cc1,"Lower_Vowels","aeiou");
    cc1 = newChrcats(cc1,"Lowercase_Consonants","bcdfghjklmnpqrstvwxyz");
    cc1 = newChrcats(cc1,"Letters","^abcdefghijklmnopqrstuvwxyz");
    cc1 = newChrcats(cc1,"Punctuation","-,.'\"'?^!");

    int ofd; //open output file
    enum {BUF_SIZE=100 };//for read/write to output file
    char buf[BUF_SIZE+1];//for read/write to output file

    //Get user created categories
    if(argc > 1 && argc %argsPerChrcat == 1){//check that correct number of arguments have been entered
        if(argc > 3){
            for (int i = 3; i < argc; i++){
                cc2=newChrcats(cc2, argv[i], argv[i+1]);
                i++;//add extra count to move to next pair     
            }
        }   
        char* arg1 = argv[1]; //input file name
        char* arg2 = argv[2];//output file name
        //Check if output is to console or to file
        if(*arg2 !='-'){ //Create file if not print to console
            int f1; //return error if file is not created
            if((f1 = creat(arg2, S_IRUSR|S_IWUSR))==-1)
                ERROR("Can't create file.");
            else{
                //Return error if output file cannot be opened
                if((ofd = open(arg2, O_WRONLY | O_CREAT | O_TRUNC, 0644))==-1){
                    ERROR("FILE NOT FOUND!");
                }
            }

        }
        //if argv[1] is "-", get input from command line
        if(*arg1 == '-'){
            while(1){
                int len = 0; //get length of user input
                printf("Please enter a string (ctrl-d or enter to stop):\n");
                char *userInput = getInput(&len); //get input from user
                //If output file specified, include user input to output file
                if(*arg2 !='-'){ 
                    if(len > 1){
                        write(ofd, "Input: ",strlen("Input: "));
                        write(ofd, userInput, strlen(userInput));
                        write(ofd, "\n",strlen("\n"));
                    }
                }
                if (len <= 1){
                    free(userInput);
                    break;
                } else{
                    if(cc1 != NULL){
                        countMatches(cc1, userInput);
                    }
                    if(cc2 != NULL){
                        countMatches(cc2, userInput);
                    }
                }
                //Free user entered input
                free(userInput);
            }
        } else{
            //Get input from file
            //Return error if output file cannot be opened
            int ifd=fileno(stdin); //input file
            if((ifd = open(arg1, O_RDONLY))<0){
                ERROR("FILE NOT FOUND!");
            }
            else {
                for(int n; ((n=read(ifd,buf,BUF_SIZE))>0);){ //while number of characters read from file >0
                    if(*arg2 !='-'){ 
                            write(ofd, "Input: ",strlen("Input: ")); //print input to output file
                            write(ofd, buf, n); //print buf to output file
                    } else{
                            write(1, "Input: ",strlen("Input: "));
                            write(1, buf, n);
                    }
                    buf[n] = '\0';
                    char* copy = charToString(buf);
                    if(cc1 != NULL){
                        countMatches(cc1, copy);
                    }
                    if(cc2 != NULL){
                        countMatches(cc2, copy);
                    }
                    free(copy);
                }
            }
            close(ifd);
            }
    //Print data
    if(*arg2 == '-'){
        //If second arg is -, print output to console
        if(cc1 != NULL){
            printf("\nBUILT-IN CATEGORIES:\n------------------------\n");
            printStrings(cc1);
        }
        if(cc2 != NULL){
            printf("\nUSER ENTERED CATEGORIES:\n------------------------\n");
            printStrings(cc2);
        }
    } else{
        char* msg;
        if(cc1 != NULL){
            msg = "\nBUILT-IN CATEGORIES:\n------------------------\n";
            printToFile(cc1, ofd, msg); 
        }
        if(cc2 != NULL){
            msg = "\nUSER ENTERED CATEGORIES:\n------------------------\n";
            printToFile(cc2, ofd,msg); 
        }
        close(ofd);
    }          
    //Free Chrcat
    freeChrcats(cc1);
    freeChrcats(cc2);
    } else if(argc == 1){
        ERROR("No input or output information entered.");
    } else{
        ERROR("Invalid number of arguments entered.");
    }
  return 0;
}

