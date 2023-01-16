//Compile: gcc -o vc vc.c -g -Wall && ./vc
// execute: ./vc
// debug: gdb ./vc

/*
*Created by Chiara Altobelli
*Created on September 4, 2022
*CS253 Homework 1 - Vowel Count
*/

/*
PURPOSE: This program takes values entered to constant array (vowels) 
and user entered data (line) and checks if the values are lowercase and counts up all of the vowels.
*/

#include <stdio.h>
#include <stdlib.h>

//Function to check if constant array values are lowercase
extern void isLower(const char array[],int len, int* c) {
  for (int i=0; i<len; i++)
      if (array[i]>='A' && array[i]<='Z'){
        *c=0; //set condition for while loop to false
      }
}

//Function to count constant array vowels
extern void checkVowel(const char a[], int len, int* b){
  for (int i = 0; i < len; i++){
    if (a[i] == 'a' || a[i]  == 'e' || a[i]  == 'i' || a[i]  == 'o' || a[i]  == 'u' || a[i]  == 'y' || a[i] == 'A' || a[i]  == 'E' || a[i]  == 'I' || a[i]  == 'O' || a[i]  == 'U' || a[i]  == 'Y')
      ++*b;
  }
}

//Function to convert user entered array values to lowercase
extern void convertToLower(char *a, int i, ssize_t len) {
    if (a[i]>='A' && a[i]<='Z'){
     a[i]-='A'-'a';
    }
}

//Function to count user entered array vowels
extern void checkUserVowel(char *a, int i, ssize_t len, int* j){
    if (a[i] == 'a' || a[i]  == 'e' || a[i]  == 'i' || a[i]  == 'o' || a[i]  == 'u' || a[i]  == 'y')
      ++*j;
}

int main() {
  //Declare variables for constant array
  const char vowels[]="aeiou"; //hardcoded array to store vowels
  int k = sizeof(vowels); //get size of constant array vowels

  //Call function to check if constant array values are lowercase
  int c=1; //create value for loop to check if values are lowercase
  isLower(vowels,k, &c);
  printf("Constant array value: %s\n", vowels);
  //Check if constant array is lowercase
  if (c==0)
    printf("Value of constant array is not in lowercase format: %s.\n", vowels);

  //Determine if character in constant array is a vowel
  int b = 0; //variable to count vowels
  checkVowel(vowels, k, &b);
  printf("The number of vowels in constant array is: %d\n", b);

  //Get user inputs
  char *line=0; //create pointer to get user inputs
  size_t n=0; 
  int j = 0; //variable to count vowels
  printf("\nPlease enter vowels on one line: ");
  ssize_t len=getline(&line,&n,stdin); //get user inputs and determine length
  if (len>0)
  {
    for (int i = 0; i < len; i++)
    {
      convertToLower(line, i, len); //convert user entry to lowercase
      checkUserVowel(line, i, len, &j); //count vowels in user entry
    }
  }
  printf("Values entered: %s", line);
  printf("Number of vowels entered by user: %d\n", j);
  free(line);

  return 0;
}