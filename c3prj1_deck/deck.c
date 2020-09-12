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

void add_card_to (deck_t * deck,card_t c){
  deck->n_cards++;
  deck->cards=realloc(deck->cards,deck->n_cards*sizeof(*deck->cards));
  card_t * temp=malloc(sizeof(*temp));
  temp[0]=c;
  deck->cards[deck->n_cards-1]=temp;
  // free(temp);
}

card_t * add_empty_card(deck_t * deck){
  card_t c;
  c.value=0;
  c.suit=NUM_SUITS;
  add_card_to(deck,c);
  return deck->cards[deck->n_cards-1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  deck_t * ans=malloc(sizeof(*ans));
  ans->n_cards=0;
  ans->cards=NULL;
  int check=0;
  for (unsigned i=0;i<52;i++){
    card_t c=card_from_num(i);
    for (unsigned j=0;j<excluded_cards->n_cards;j++){
      if (c.value==excluded_cards->cards[j]->value && c.suit==excluded_cards->cards[j]->suit){
	check=1;
	break;
      }     
    }
    if (check==1) {
      check=0;
      continue;
    }
    add_card_to(ans,c);
  }
  return ans;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  deck_t * exclude=malloc(sizeof(*exclude));
  exclude->n_cards=0;
  exclude->cards=NULL;
  for (size_t i=0;i<n_hands;i++){
    deck_t * h=hands[i];
    for (size_t j=0;j<h->n_cards;j++){
      add_card_to(exclude,*h->cards[j]);
    }
  }
  deck_t * ans=make_deck_exclude(exclude);
  free_deck(exclude);
  return ans;
}

void free_deck(deck_t * deck){
  for (size_t i=0;i<deck->n_cards;i++){
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
