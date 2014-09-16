#include<stdio.h>
#include<stdlib.h>
int f(int x, int y){
int u;
u = x*y;
printf("in f\n");
return( x+u+y );
}
int g(int* p, int* q){
int v;
v = *p + *q;
printf("in g, before f\n");
*q = f(v, *p);
printf("in g, after f\n");
return( v-*q );
}
int main(void){
int a=1, b=2, c=3;
printf("in main, before f and g\n");
a = f(a, b);
b = g(&b, &c);
printf("in main, after f and g\n");
printf("a = %d, b = %d, c = %d\n", a, b, c);
return(EXIT_SUCCESS);
}