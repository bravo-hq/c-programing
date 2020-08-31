#include <stdlib.h>
#include <stdio.h>

unsigned power (unsigned x, unsigned y);

int main(){
  
  unsigned x=0;
  unsigned y=0;
  if (power(x,y)!=1){printf("test1"); return EXIT_FAILURE;}

  x=0; y=10;
  if (power(x,y)!=0){printf("test2"); return EXIT_FAILURE;}

  x=1;y=2;
  if (power(x,y)!=1){printf("test3"); return EXIT_FAILURE;}

  x=2;y=1;
  if (power(x,y)!=2){printf("test4"); return EXIT_FAILURE;}

  x=3;y=2;
  if (power(x,y)!=9){printf("test5"); return EXIT_FAILURE;}
  
  //  x=2.0; y=2;
  //  if (power(x,y)!=4){printf("test6"); return EXIT_FAILURE;}

  x=-1; y=1;
  if (power(x,y)!=4294967295){printf("test6"); return EXIT_FAILURE;}

  //  x=1;y=-2;
  //  if (power(x,y)!=0){printf("test8"); return EXIT_FAILURE;}

  return EXIT_SUCCESS;
}
