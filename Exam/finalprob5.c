#include<stdio.h>
#include<stdlib.h>

char* cat(char* s1, char*s2){
  char temp = *s1;
  int i = 0;
  while(temp!='\0'){
    temp = s1[i];
    i++;
  }
  char temp2 = *s2;
  int j = 0;
  while(temp!='\0'){
    temp2 = s1[j];
    j++;
  }
  char* s3 = calloc((i+j+1),sizeof(char));
  int k;
  for(k=1; k<i; k++){
    s3[k] = s1[k];
  }
  int l;
  for(l=i; l<(i+j); l++){
    s3[l]=s2[i+l];
  }

  return s3;
}

int main(void){
  char* s1 = "one";
  char* s2 = "five";
  char* s3 = cat(s1, s2);
  printf("%s", s3);
  
  return(EXIT_SUCCESS);
}
