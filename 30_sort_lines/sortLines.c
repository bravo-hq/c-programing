#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
  char ** line=NULL;
  char * curr=NULL;
  size_t sz;  
  size_t i=0;
  
  if (argc==1){
    while(getline(&curr,&sz,stdin)>=0){
      line=realloc(line,(i+1)*sizeof(*line));
      line[i]=curr;
      curr=NULL;
      i++;
    }
    free(curr);
    sortData(line,i);
    for (size_t j=0;j<i;j++){
      printf("%s",line[j]);
      free(line[j]);
    }
    free(line);
    return EXIT_SUCCESS;
  }

  if (argc>1){
    for (size_t h=1; h<argc; h++){
      FILE * f= fopen(argv[h],"r");
      if (f==NULL){
	perror("could not open the file");
	return EXIT_FAILURE;
      }
      while(getline(&curr,&sz,f)>=0){
	line=realloc(line,(i+1)*sizeof(*line));
	line[i]=curr;
	curr=NULL;
	i++;
      }
      sortData(line,i);
      for (size_t j=0;j<i;j++){
	printf("%s",line[j]);
	free(line[j]);
      }
      i=0;
      //    curr=NULL;
      // line=NULL;
    }
    free(curr);
    free(line);
  } 
  return EXIT_SUCCESS;
}

