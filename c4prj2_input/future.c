#include <stdlib.h>
#include <stdio.h>
#include "deck.h"
#include "eval.h"
#include "cards.h"
#include "future.h"
#include <string.h>

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
  if (fc->n_decks<index+1){
    fc->decks=realloc(fc->decks,(index+1)*sizeof(*fc->decks));
    fc->n_decks=index+1;
    fc->decks[index].n_cards=0;
    fc->decks[index].cards=NULL;
    for (size_t i=0;i<fc->n_decks;i++){
      if (fc->decks[i].n_cards<1){
	fc->decks[i].cards=NULL;
      }
    }
  }else{
    fc->decks=realloc(fc->decks,fc->n_decks*sizeof(*fc->decks));
  }
  fc->decks[index].n_cards++;
  fc->decks[index].cards=realloc(fc->decks[index].cards,fc->decks[index].n_cards*sizeof(card_t *));
  fc->decks[index].cards[fc->decks[index].n_cards-1]=ptr;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  if (fc->n_decks==0 || fc->n_decks > deck->n_cards){
    perror("no future decks");
    return;
  }
  for (size_t i=0; i<fc->n_decks;i++){
    deck_t temp=fc->decks[i];
    for (size_t j=0;j<temp.n_cards;j++){
     *temp.cards[j]=*deck->cards[i];
    }
  }
}
