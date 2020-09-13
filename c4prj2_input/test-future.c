#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "future.h"
#include "eval.h"
#include "deck.h"
#include "cards.h"
#include "input.h"

int main(){
  FILE * f =fopen("input.txt","r");
  future_cards_t* fc = (future_cards_t*)calloc(1,sizeof(future_cards_t));
  fc->decks = (deck_t*)calloc(1,sizeof(deck_t));
  fc->n_decks = 0;
  size_t num_hands = 5;
  size_t* n_hands = &num_hands;
  deck_t ** data=read_input(f,n_hands,fc);
  for(size_t i=0;i<(*n_hands);i++){
  print_hand(data[i]);
  printf("\n");
  }
  deck_t * deck=build_remaining_deck(data,*n_hands);
  shuffle(deck);
  shuffle(deck);
   for (size_t i=0;i<fc->n_decks;i++){
       printf("fc deck %zu contains %zu cards\n",i,fc->decks[i].n_cards);
    continue;
  }
  future_cards_from_deck(deck,fc);
  for(size_t i=0;i<(*n_hands);i++){
    print_hand(data[i]);
    printf("\n");
  }
  free_deck(deck);
  for (size_t i=0;i<(*n_hands);i++){
    free_deck(data[i]);
  }
  free(data);
  // for (size_t i=0;i<fc->n_decks;i++){
  // print_hand(fc->decks);
  // }
  return EXIT_SUCCESS;
}
