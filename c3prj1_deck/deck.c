#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_hand(deck_t * hand){
  for (size_t i=0; i<hand->n_cards; i++){
    print_card(*(hand->cards)[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  card_t temp;
  for (size_t i=0; i<d->n_cards; i++){
    temp=*(d->cards)[i];
    if (temp.value==c.value && temp.suit==c.suit) return 1;
  }
  return 0;
}

void shuffle(deck_t * d){
  card_t * temp;
  for (size_t i=0; i<d->n_cards; i++){
    size_t j = i + rand() / (RAND_MAX / (d->n_cards - i) + 1);
    temp = (d->cards)[j];
    (d->cards)[j]=(d->cards)[i];
    (d->cards)[i]=temp;
  }
}

void assert_full_deck(deck_t * d) {
  int temp=0;
  card_t temp2;
  for (size_t i=0; i<52; i++){
    for (size_t j=0; j<d->n_cards; j++){
      temp2=*(d->cards)[j];
      if (temp2.value==card_from_num(i).value && temp2.suit==card_from_num(i).suit) {
	temp++;}
    }
    assert(temp==1);
    temp=0;
  }
}
