#include <stdlib.h>
#include <stdio.h>
#include "eval.h"
#include "deck.h"
#include "cards.h"
#include <string.h>

int main (){
  // printf("hello\n");
  deck_t * deck = malloc(sizeof(*deck));
    deck->n_cards=3;
    
    card_t c =card_from_num(30);
    card_t a =card_from_num(10);
    card_t b =card_from_num(20);
    deck->cards=malloc(deck->n_cards*sizeof(*deck->cards));
    deck->cards[0]=&a;
    deck->cards[1]=&b;
    deck->cards[2]=&c;
    // add_card_to(deck,card_from_num(40));
    // add_card_to(deck,card_from_num(50));
    card_t * p=add_empty_card(deck);
    printf("%p\n",(void *)p);
    print_hand(deck);
    printf("\n");
    deck_t * new =build_remaining_deck(&deck,1);
    print_hand(new);
    /*    print_card(*p);
    deck_t *new=make_deck_exclude(deck);
    printf("\n");
    printf("%d\n",(int)new->n_cards);
    print_hand(new);
    // printf("%d",c.suit);
    // card_t * c1=add_empty_card(*/
 return EXIT_SUCCESS;
}
