#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate (char matrix[10][10]){
  char temp[10][10];
  memcpy(temp,matrix,10*10*sizeof(char));
  for (size_t i=0;i<10;i++){
    for(size_t j=0;j<10;j++){
      matrix[j][9-i]=temp[i][j];     
    }
  }
}
