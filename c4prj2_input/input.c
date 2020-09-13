#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "future.h"
#include "eval.h"
#include "deck.h"
#include "cards.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc){
  // Returns first token
  char str1[strlen(str)];
  strcpy(str1,str);
  char* token = strtok(str1,(const char *) " ");
  if (token ==NULL){
    perror("could not read the start of the sentence\n");
    exit (EXIT_FAILURE);
  }
  char ** data= malloc(sizeof(*data));
  int i=0;
  // Keep printing tokens while one of the
  // delimiters present in str[].
  while (token != NULL) {
    i++;
    data=realloc(data,i*sizeof(*data));
    char * check=strchr(token,'\n');
    if (check!=NULL){
      *check='\0';
    }
    data[i-1]=token;
    token = strtok(NULL,(const char *) " ");
  }
  if (i<5){
    perror("not enough hands\n");
    exit(EXIT_FAILURE);
  }
  deck_t * ans=malloc(sizeof(*ans));
  ans->n_cards=0;
  ans->cards=NULL;
  for (size_t j=0; j<i;j++){
    if (data[j][0]=='?'){
      card_t * c= add_empty_card(ans);
      char * temp=data[j];
      temp++;
      add_future_card(fc,atoi(temp),c);
      continue;
    }
    add_card_to(ans,card_from_letters(data[j][0],data[j][1]));
  }
  free(data);
  return ans;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
  char * curr=NULL;
  size_t sz;
  int i=0;
  deck_t ** ans=malloc(sizeof(*ans));
  
  while(getline(&curr,&sz,f)>=0){
    ans=realloc(ans,(i+1)*sizeof(*ans));
    ans[i]=hand_from_string(curr,fc);
    free(curr);
    curr=NULL;
    i++;
  }
  free(curr);
  *n_hands=i;
  return ans;
}
