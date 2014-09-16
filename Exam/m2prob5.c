#include<stdio.h>
#include<stdlib.h>
int main(void){
  int i, j;
  double x = 4.2, y;
  double * A = calloc(4, sizeof(double));
  double B[] = {1.2, 5.3, 2.1, 3.4};
  double *p, *q;
  p = malloc(sizeof(double));
  y = x+2;
  q = &y;
  *p = *q + 2.5;
  for(i=0; i<4; i++){
    j = 3-i;
    *(A+i) = B[j] + i;
  }
  printf("%f, %f, %f, %f\n", *A, *B, *p, *q);
  A = B;
  printf("%f, %f, %f, %f\n", *A, *(A+1), *(A+2), *(A+3) );
  return(EXIT_SUCCESS);
}
