//Compile: gcc -o charcat sq sq.c -g -Wall
//Execute: ./sq
//Debug: gdb ./sq

#include <stdio.h>
#include <stdlib.h>
#include "ChrCat.h"

/*
*Created by Chiara Altobelli
*Created on September 24, 2022
*CS253 Homework 2 - The Static Quo
*/

/*
PURPOSE: This program takes user entered data (getInput) and compares to an array of struct character pointers
(vowels, consonants, lower, upper, digits, letter, punctuation, asender, descender, curvy, sticky).
A user can change these categories and should change the #define SIZE value in ChrCat.h to account for the number
of categories to test user input against. The program counts all of the matching values for each category, returns
the output as a string and provides the user with the total for each category.
*/

static char *getstr(ssize_t *len);

int main() {
  //Read user input
  ssize_t len = 0; //length of user string
  char *getInput = getstr(&len); //get input from user

  //count up each instance of match between user entered data and category data
  testCategories(getInput, len);

  free(getInput);

  return 0;
}

//Get user input, return length of string
static char *getstr(ssize_t *len) 
{
  printf("Please enter a string: \n");
  char *line=0;
  size_t n=0;
  *len=getline(&line,&n,stdin);
  if (len>=0) {
    if (line[*len-1]=='\n')
      line[*len-1]=0;
    return line;
  }
  free(line);
  return 0;
}