#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

kvpair_t * rectifyData(char * line){
  kvpair_t * KV=malloc(sizeof(*KV));
  char * temp= strchr(line,'\n');
  *temp='\0';
  KV->key=line;
  KV->value=line;
  return KV;
}

kvarray_t * readFile(const char * filename){
  FILE * f = fopen(filename,"r");
  if (f==NULL){
    fprintf(stderr,"could not open '%s' file\n",filename);
    exit(EXIT_FAILURE);
  }
  
  char ** line=NULL;
  char * curr=NULL;
  size_t sz;
  int i=0;
  
  while(getline(&curr,&sz,f)>=0){
    line=realloc(line,(i+1)*sizeof(*line));
    line[i]=curr;
    // free(curr);
    curr=NULL;
    i++;
  }
  free(curr);
  kvarray_t * data=malloc(sizeof(*data));
  data->length=i;
  data->pair=malloc(i*sizeof(*data->pair));
  for (size_t j=0;j<i;j++){
    data->pair[j]=rectifyData(line[j]);
  }
  data->line=line;
  if(fclose(f)!=0){
    perror("there was a problem with closing the file\n");
    exit (EXIT_FAILURE);
  }
  return data;
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * c= createCounts();

  kvarray_t * data=readFile(filename);
  for (size_t i=0;i<data->length;i++){
    addCount(c,lookupValue(kvPairs,data->pair[i]->key));
  }
  freeKVs(data);
  return c;
}

void freeName (char * fname){
  free(fname);
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc<3){
    perror("not enough arguments");
    exit (EXIT_FAILURE);
  }
  kvarray_t * kv=readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for (size_t i=2;i<argc;i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i],kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName=computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName,"w");
    if (f==NULL){
      fprintf(stderr,"could not open the '%s' file\n",outName);
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c,f);
    //close f
    if (fclose(f)!=0){
      fprintf(stderr,"could not close the '%s' file\n",outName);
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    freeCounts(c);
    freeName(outName);
  }
 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
