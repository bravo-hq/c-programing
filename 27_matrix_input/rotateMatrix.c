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

int main (int argc, char ** argv){
  if (argc != 2){
    fprintf(stderr,"too many or not enough argumets");
    exit (EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1],"r");
  if (f==NULL){
    perror("could not open the file");
    exit (EXIT_FAILURE);
  }
  char m[10][10];
  int i=0;
  while (fgets(m[i],12,f)!=NULL){
    if (strchr(m[i],'\n')==NULL){
      fprintf(stderr,"line %d is too long",i);
       exit (EXIT_FAILURE);
     }
    i++;
    if (i==10) break;
  }
  rotate(m);
  for (int i =0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", m[i][j]);
      if (j==9) printf("\n");
    }
  }
  return 0;
}
