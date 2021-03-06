#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * ans=malloc(sizeof(*ans));
  ans->unkwn=0;
  ans->size=0;
  ans->arr=NULL;
  return ans;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name==NULL){
    c->unkwn++;
    return;
  }
  for (size_t i=0;i<c->size;i++){
    if (strcmp(c->arr[i].name,name)==0){
      c->arr[i].count++;
      return;
    }
  } 
    c->size++;
    c->arr=realloc(c->arr,c->size*sizeof(*c->arr));
    c->arr[c->size-1].count=1;
    c->arr[c->size-1].name=name;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i=0;i<c->size;i++){
    fprintf(outFile,"%s: %d\n",c->arr[i].name,c->arr[i].count);
  }
  if (c->unkwn==0) return;
  fprintf(outFile,"<unknown> : %d\n",c->unkwn);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  //  for(size_t i=0; i<c->size;i++){
  free(c->arr);
  //  }
  free(c);
}
