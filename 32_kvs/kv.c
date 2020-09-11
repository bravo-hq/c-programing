#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t * splitValue(char * line){
  kvpair_t * KV=malloc(sizeof(*KV));
  char * temp= strchr(line,'=');
  *temp='\0';
  KV->key=line;
  temp++;
  char * temp2 = strchr(temp,'\n');
  *temp2='\0';
  KV->value=temp;
  return KV;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f= fopen(fname,"r");
  if (f==NULL){
    perror("there is a problem with opennig the file\n");
    exit (EXIT_FAILURE);
  }
  char ** line=NULL;
  char * curr=NULL;
  size_t sz;
  int i=0;
  //  kvarray_t * data=malloc(sizeof(*data));
  //data->pair=NULL;
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
    data->pair[j]=splitValue(line[j]);
  }
  data->line=line;
/*  for (size_t j=0;j<i;j++){
    free(line[j]);
  }
  free(line);*/
  if(fclose(f)!=0){
    perror("there was a problem with closing the file\n");
    exit (EXIT_FAILURE);
  }
  return data;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  
  for (size_t i=0;i<pairs->length;i++){
    free(pairs->line[i]);
  }
  free(pairs->line);
  for (size_t j=0;j<pairs->length;j++){
      free(pairs->pair[j]);
  }
  free(pairs->pair);
  free(pairs);  
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i=0;i<pairs->length;i++){
     printf("key = '%s' value = '%s'\n",pairs->pair[i]->key,pairs->pair[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i=0;i<pairs->length;i++){
    if (strcmp(key,pairs->pair[i]->key)==0){
      return pairs->pair[i]->value;
    }
  }
  return NULL;
}
