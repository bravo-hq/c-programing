#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(){
  int arr[100];
  if (maxSeq(arr,0)!=0) return EXIT_FAILURE;

  int arr1[]={1,2,1,3,5,7,2,4,6,9};
  if (maxSeq(arr1,10)!=4) return EXIT_FAILURE;

  int arr2[]={1,2,3,4};
  if (maxSeq(arr2,4)!=4) return EXIT_FAILURE;

  int arr3[]={1,2,2,4};
  if (maxSeq(arr3,4)!=2) return EXIT_FAILURE;

  int arr4[]={3,-4,5,6};
  if (maxSeq(arr4,4)!=3) return EXIT_FAILURE;

  int arr5[]={10,9,7,6};
  if (maxSeq(arr5,4)!=1) return EXIT_FAILURE;

  return EXIT_SUCCESS;
}






