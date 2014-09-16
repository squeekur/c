// April Dawn Kester
// akester
// CMPS 12M
// August 7, 2013
// Used for test Dictionary.c
// DictionaryTest.c
// No special instructions

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

#define MAX_LEN 180

int main(int argc, char* argv[]){
   Dictionary A = newDictionary();
   int e = isEmpty(A);
   int s = size(A);
   printf("%d, %d\n", e, s);
   char* k;
   char* v;
   char* word1[] = {"one","two","three","four","five","six","seven"};
   char* word2[] = {"foo","bar","blah","galumph","happy","sad","blue"};
   int i;

   for(i=0; i<7; i++){
      insert(A, word1[i], word2[i]);
   }

   printDictionary(stdout, A);

   e = isEmpty(A);
   s = size(A);
   printf("%d, %d\n", e, s);

   for(i=0; i<7; i++){
      k = word1[i];
      v = lookup(A, k);
      printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
   }

   // insert(A, "five", "glow"); // error: key collision
   
   delete(A, "one");
   delete(A, "three");
   delete(A, "seven");

   printDictionary(stdout, A);

   for(i=0; i<7; i++){
      k = word1[i];
      v = lookup(A, k);
      printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
   }
   
   // delete(A, "one");  // error: key not found
    
   printf("%s\n", (isEmpty(A)?"true":"false"));
   printf("%d\n", size(A));
   makeEmpty(A);
   printf("%s\n", (isEmpty(A)?"true":"false"));
   
   freeDictionary(&A);

   return(EXIT_SUCCESS);
}
