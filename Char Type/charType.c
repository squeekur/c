/* April Dawn Kester
akester
CMPS 12M
July 24, 2013
Reads a file in, classifies characters by line to out file
charType.c
No special instructions*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include<string.h>

#define MAX_STRING_LENGTH 100


//<------MY FUNCTION PROTOTYPE DONE
void extract_chars(char* s, char* a, char* d, char* p, char* w);

// function main which takes command line arguments DONE 
int main(int argc, char* argv[]){
   FILE* in;          // handle for input file                  
   FILE* out;         // handle for output file                 
   char* line;        // string holding input line              
   char* alphabetic;  //<-----MY STRING HOLDING ALPHABETIC CHARS
   char* digit;      //<-----MY STRING HOLDING DIGIT CHARS
   char* punctuation; //<-----MY STRING HOLDING PUNCTUATION CHARS
   char* whitespace;  //<-----MY STRING HOLDING WHITESPACE CHARS

   // check command line for correct number of arguments DONE
   if( argc != 3 ){
      printf("Usage: %s input-file output-file\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // open input file for reading DONE
   if( (in=fopen(argv[1], "r"))==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   // open output file for writing DONE
   if( (out=fopen(argv[2], "w"))==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   // allocate strings on the heap DONE 
   line = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   alphabetic = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   digit = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   punctuation = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   whitespace = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   assert(line!=NULL && alphabetic!=NULL && digit!=NULL && punctuation!=NULL && whitespace!=NULL);

   // read each line in input file, extract characters DONE
   int i=1; 
   while( fgets(line, MAX_STRING_LENGTH, in) != NULL ){
     extract_chars(line, alphabetic, digit, punctuation, whitespace); //<----------------HERE IS MY FUNCTION CALL
     fprintf(out, "line " "%d" " contains:\n", i);

     if(strlen(alphabetic)==1){ 
     fprintf(out, "%zu" " alphabetic character: " "%s\n", strlen(alphabetic), alphabetic);//<---------------HERE IS MY PRINT LINE TO FILE
     }else fprintf(out, "%zu" " alphabetic characters: " "%s\n", strlen(alphabetic), alphabetic);

     if(strlen(digit)==1){
     fprintf(out, "%zu" " numeric character: " "%s\n", strlen(digit), digit);
     }else fprintf(out, "%zu" " numeric characters: " "%s\n", strlen(digit), digit);

     if(strlen(punctuation)==1){
     fprintf(out, "%zu" " punctuation character: " "%s\n", strlen(punctuation), punctuation);
     }else fprintf(out, "%zu" " punctuation characters: " "%s\n", strlen(punctuation), punctuation);
     
     if(strlen(whitespace)==1){
       fprintf(out, "%zu" " whitespace character: " "%s\n", strlen(whitespace), whitespace);
     }else fprintf(out, "%zu" " whitespace characters: " "%s\n", strlen(whitespace), whitespace);

     i++;
   }

   // free heap memory DONE
   free(line);
   free(alphabetic);
   free(digit); 
   free(punctuation); 
   free(whitespace); 

   // close input and output files DONE 
   fclose(in);
   fclose(out);

   return EXIT_SUCCESS;
}

// my function definition DONE
void extract_chars(char* s, char* a, char* d, char* p, char* w){
  int i=0, j=0, v=0, x=0, q=0;
  while(s[i]!='\0' && i<MAX_STRING_LENGTH){
    if(isalpha((char)s[i])){
      a[j++] = s[i];
      i++;
    }else if(isdigit((int)s[i])){
      d[v++] = s[i];
      i++;
    }else if(ispunct((char)s[i])){
      p[x++] = s[i];
      i++;
    }else if(isspace((char)s[i])){
      w[q++] = s[i];
      i++;
    }else i++;
  }
  a[j] = '\0';
  d[v] = '\0';
  p[x] = '\0';
  w[q] = '\0';
}



