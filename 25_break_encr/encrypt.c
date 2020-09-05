#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void freq(FILE * f, int * arr){
  int c;
  while ((c = fgetc(f)) != EOF) {
    printf("%c",c);
    if (isalpha(c)) {
      c-='a';
      arr[c]++;      
    }
  }
}

int keycheck(int arr[]){
 int  max = arr[0];
 int loc=0;

  for (size_t i = 0; i < 26; i++)
    {
      if (arr[i] > max)
	{
	  max  = arr[i];
	  loc = i;
	}
    }
  int key = loc+22;
  key = key%26;
  return key;
}

int main (int argc, char ** argv){
  if (argc!=2){
    fprintf(stderr,"not enough arguments.\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int arrf[26]={0};
  freq(f,arrf);
  int key=keycheck(arrf);
  if (key>=0 && key <26){
    printf("%d is the key\n",key);
    return EXIT_SUCCESS;
  }
  fprintf(stderr,"failed.\n");
  return EXIT_FAILURE;
}
