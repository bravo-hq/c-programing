#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value<=14 && c.value>=2);
  assert(c.suit>=SPADES && c.suit<=CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  switch (r){
  case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH"; break;
  case FOUR_OF_A_KIND: return"FOUR_OF_A_KIND"; break;
  case FULL_HOUSE: return"FULL_HOUSE"; break;
  case FLUSH: return"FLUSH"; break;
  case STRAIGHT: return"STRAIGHT"; break;
  case THREE_OF_A_KIND: return"THREE_OF_A_KIND"; break;
  case TWO_PAIR: return"TWO_PAIR"; break;
  case PAIR: return"PAIR"; break;
  default: return"NOTHING";
    }

}

char value_letter(card_t c) {
  char ans='?';
  switch (c.value){
  case 11:
    ans='J';
    break;
  case 12:
    ans='Q';
    break;
  case 13:
    ans='K';
    break;
  case 14:
    ans='A';
    break;
  case 10:
    ans='0';
    break;
  default:
    ans='?';
  }
   if (c.value<=9 && c.value>=2){
     ans='0';
     ans=ans+c.value;
  }
  
  return ans;
}


char suit_letter(card_t c) {
  char ans='0';
  switch (c.suit){
  case SPADES:
    ans='s';
    break;
  case HEARTS:
    ans='h';
    break;
  case DIAMONDS:
    ans='d';
    break;
  case CLUBS:
    ans='c';
    break;
  default:
    break;
   }
  return ans;
  
}

void print_card(card_t c) {
  char ans;
  ans=value_letter(c);
  printf("%c",ans);
  ans=suit_letter(c);
  printf("%c",ans);
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  switch (value_let){
  case '2': temp.value=2; break;
  case '3': temp.value=3; break;
  case '4': temp.value=4; break;
  case '5': temp.value=5; break;
  case '6': temp.value=6; break;
  case '7': temp.value=7; break;
  case '8': temp.value=8; break;
  case '9': temp.value=9; break;
  case '0': temp.value=10; break;
  case 'A': temp.value=14; break;
  case 'J': temp.value=11; break;
  case 'K': temp.value=13; break;
  case 'Q': temp.value=12; break;
  default: printf("value missmatch"); //return EXIT_FAILURE;
  }
  switch (suit_let){
  case 'c': temp.suit=CLUBS; break;
  case 's': temp.suit=SPADES; break;
  case 'd': temp.suit=DIAMONDS; break;
  case 'h': temp.suit=HEARTS; break;
  default: printf("suit missmatch");//return EXIT_FAILURE;
  }
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  int value=c%13;
  int suit=c/13;
  switch (value){
  case 1: temp.value=14; break;
  case 2: temp.value=2; break;
  case 3: temp.value=3; break;
  case 4: temp.value=4; break;
  case 5: temp.value=5; break;
  case 6: temp.value=6; break;
  case 7: temp.value=7; break;
  case 8: temp.value=8; break;
  case 9: temp.value=9; break;
  case 0: temp.value=10; break;
  case 10: temp.value=12; break;
  case 11: temp.value=11; break;
  case 12: temp.value=13; break;
  default: break;
  }
  switch (suit){
  case 0: temp.suit=CLUBS; break;
  case 1: temp.suit=SPADES; break;
  case 2: temp.suit=DIAMONDS; break;
  case 3: temp.suit=HEARTS; break;
  default: break;
  }
  return temp;
}
