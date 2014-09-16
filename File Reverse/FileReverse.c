/* April Dawn Kester
akester
CMPS 12M
July 14, 2013
Reads a file in reverses strings and out to file
FileReverse.c
No special instructions*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void stringReverse(char* s){
  int i = 0;
  int j = strlen(s)-1;
  while(i<=j){  
    int temps1 = s[i];
    int temps2 = s[j];
    s[i] = temps2;
    s[j] = temps1;
    i++;
    j--;
  }
  }

int main(int argc, char * argv[]){
  FILE *in, *out;   // handles for input and output files 
  char word[256];   // char array to store words from input file 

  // check command line for correct number of arguments
  if( argc != 3 ){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // open input file for reading 
  in = fopen(argv[1], "r");
  if( in==NULL ){
    printf("Unable to read from file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // open output file for writing 
  out = fopen(argv[2], "w");
  if( out==NULL ){
    printf("Unable to write to file %s\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  // read words from input file, print on separate lines to output file 
  while(fscanf(in, " %s", word)!=EOF){
    stringReverse(word);   
    fprintf(out, "%s\n", word);
  }

  // close input and output files 
  fclose(in);
  fclose(out);

  return(EXIT_SUCCESS);
}

