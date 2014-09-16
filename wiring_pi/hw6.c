/* April Dawn Kester
akester
CMPE 12
December 4, 2013
Reads a string in and does search for additional string
hw6.c
No special instructions*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int location;

int findString(char* a, char* b){
  int i;
  int j;
  int temp1 = 0;
  int temp2 = 0;
  int flag;

  while(a[temp1]!='\0')
	temp1++;
  while (b[temp2]!='\0')
	temp2++;

  for(i=0; i<temp1-temp2; i++){
	for(j=i; j<i+temp2; j++){
		flag=1;
		location=i;
		if(a[j]!=b[j-i]){
			flag=0;
			break;
		}
	}
	if(flag==1)
		break;
	}
return flag;
}

   


int main(int argc, char * argv[]){  

  // check command line for correct number of arguments
  if( argc != 3 ){
    printf("Usage: %s requires two strings as args!\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char* wordOne = argv[1];
  char* wordTwo = argv[2];

  if(strlen(wordTwo) > strlen(wordOne)){
  printf("Your second string is not a substring\n");
  exit(EXIT_FAILURE);
}
  
  int status = findString(wordOne, wordTwo);
  
  if (status==1)
	printf("substring FOUND at %d \n", location);
  else
	printf("substring NOT FOUND\n");

  return(EXIT_SUCCESS);
}

