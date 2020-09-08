#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  char * fileOName=malloc((strlen(inputName)+8)*sizeof(*fileOName));
  strcpy(fileOName,inputName);
  strcat(fileOName,".counts");
  //  char final[strlen(fileOName)];
  //  memcpy(final,fileOName,strlen(fileOName)+1);
  //  free(fileOName);
  return fileOName;
}
