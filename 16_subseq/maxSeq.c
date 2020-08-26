#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n){
  if (n==0) return 0;

  int count=1;
  int pcount=1;
  int current;
  int perivious=array[0];
  for (size_t i=0;i<n;i++){
    current=array[i];
    if (current>perivious){
      count++;
    }
    if (current<=perivious){
      if (pcount<count) pcount=count;
      count=1;
    }
    perivious=current;
  }
  return pcount;
}
