#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

void print_card_stderr(card_t c) {
  char ans=value_letter(c);
  fprintf(stderr,"%c",ans);
  ans=suit_letter(c);
  fprintf(stderr,"%c",ans);
}

void print_hand_stderr(deck_t * hand){
  for (size_t i=0; i<hand->n_cards; i++){
    print_card_stderr(*(hand->cards)[i]);
    printf(" ");
  }
}

int card_ptr_comp(const void * vp1, const void * vp2);


int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  if (argc>3 || argc<2){
    perror("not enough arguments");
    exit (EXIT_FAILURE);
  }
  size_t MontCar=10000;
  if (argc==3){
    MontCar=atoi(argv[2]);
  }
  FILE * f=fopen(argv[1],"r");
  if (f==NULL){
    perror("could not open the file");
    exit(EXIT_FAILURE);
  }
  size_t * n_hands=calloc(1,sizeof(*n_hands));
  future_cards_t * fc=malloc(sizeof(*fc));
  fc->n_decks=0;
  fc->decks=NULL;
  deck_t ** data=read_input(f,n_hands,fc);
  deck_t * deck=build_remaining_deck(data,*n_hands);
  int * arr=calloc(*n_hands+1,sizeof(*arr));
  for (size_t i=0;i<MontCar;i++){
    //fprintf(stderr,"i : %zu\n",i);
    shuffle(deck);
    future_cards_from_deck(deck,fc);
    deck_t * max=data[0];
    if (i==17482){
      qsort(data[0]->cards,data[0]->n_cards,sizeof(data[0]->cards[0]),card_ptr_comp);
      qsort(data[1]->cards,data[1]->n_cards,sizeof(data[1]->cards[0]),card_ptr_comp);
      qsort(data[2]->cards,data[2]->n_cards,sizeof(data[2]->cards[0]),card_ptr_comp);
      print_hand(data[0]);
      printf("\n");
      print_hand(data[1]);
      printf("\n");
      print_hand(data[2]);
      printf("\n");
    }
    int max_idx=0;
    int tie=1;
    for(size_t j=1;j<*n_hands;j++){
      int result=compare_hands(max,data[j]);
      switch (result){
      case -1:
	max=data[j];
	max_idx=j;
	tie=0;
	break;
      case 1:
	tie=0;
	break;
      default:
	tie=1;
      }
    }
    if (tie==1){
      arr[*n_hands]++;
    }else{
      arr[max_idx]++;
    }
  }
  for(size_t i=0;i<*n_hands;i++){
    printf("Hand %zu won %u / %u times (%.2f%%)\n",i,arr[i],(unsigned)MontCar,(double)arr[i]/(double)MontCar*100);  
  }
  printf("And there were %u ties\n",arr[*n_hands]);
  free(arr);
  free_deck(deck);
  for(size_t i=0;i<*n_hands;i++){
    free_deck(data[i]);
  }
  free(data);
  if (fc->decks!=NULL){
    free(fc->decks->cards);
  }
  free(fc->decks);
  free(fc);
  free(n_hands);
  if (fclose(f)!=0){
    perror("could not close the file\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
