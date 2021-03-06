#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * cp1=vp1;
  const card_t * const * cp2=vp2;
  if ((*cp1)->value - (*cp2)->value != 0){
    return (*cp2)->value - (*cp1)->value;
  }
  else if ((*cp2)->suit - (*cp1)->suit !=0){
    return (*cp2)->suit - (*cp1)->suit;
  }
  return 0;
}

suit_t flush_suit(deck_t * hand) {
  int s=0;
  int c=0;
  int h=0;
  int d=0;
  for (size_t i=0;i<hand->n_cards;i++){
    card_t temp=*(hand->cards)[i];
    switch (temp.suit){
    case SPADES:
      s++;
      break;
    case HEARTS:
      h++;
      break;
    case DIAMONDS:
      d++;
      break;
    case CLUBS:
      c++;
      break;
    default:
      break;
    }
  }
  if (s>=5) return SPADES;
  else if (h>=5) return HEARTS;
  else if (c>=5) return CLUBS;
  else if (d>=5) return DIAMONDS;
  else  return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned temp=arr[0];
  for (size_t i=0;i<n;i++){
    if (arr[i]>temp) temp=arr[i];
  }
  return temp;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  for (size_t i=0; i<n; i++){
    if (match_counts[i]==n_of_akind) return i;
  }
  exit(EXIT_FAILURE);
}

ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  card_t temp=*(hand->cards)[match_idx];
  for (size_t i=0;i<hand->n_cards;i++){
    if ((hand->cards)[i]->value==temp.value) continue;
    if (match_counts[i]>1) return i;
  }
  return -1;
}

int check_straight(deck_t *hand,size_t index, suit_t fs,int n){
  card_t perv=(*(hand->cards)[index]);
  int temp=1;
  int countf=1;
  switch(fs){
  case NUM_SUITS:
    for (size_t i=index+1; i<hand->n_cards;i++){
      card_t current=(*(hand->cards)[i]);
      if (perv.value-current.value==0){
	perv=current;
	if(temp>=n) return 1;
	continue;
      } else if (perv.value-current.value==1){
	temp++;
	countf++;
	perv=current;
	if (temp>=n) return 1;
      } else {
	if (temp>=n) return 1;
	countf++;
	temp=1;
	perv=current;
      }
      if (countf==n){
	if (temp>=n) return 1;
      break;
      }
    }
    return 0;
    break;
  default:;
    int check=-1;
    for (size_t i=index+1; i<hand->n_cards;i++){
      card_t current=(*(hand->cards)[i]);
      if (i==index+1){
	if (perv.suit != fs) break;
      }
      if (perv.value-current.value==0){
	if (check !=-1){
	  if (current.suit==fs){
	    temp++;
	    countf++;
	    check=-1;
	  }
	}
	perv=current;
	if(temp>=n) return 1;
	continue;
      } else if (perv.value-current.value==1 && current.suit==fs){
	if (check !=-1){
	  if (perv.suit!=fs){
	    // temp++;
	    // countf++;
	    check=-1;
	    break;
	  }
	}
	temp++;
	countf++;
	perv=current;
	if (temp>=n) return 1;
      } else if (perv.value - current.value==1 && (int)perv.suit-(int)current.suit>0){
	check=0;
	perv=current;
	if(temp>=n) return 1;
	continue;	
      } else {
	if (temp>=n) return 1;
	countf++;
	temp=1;
	perv=current;
      }
      if (countf==n){
	if (temp>=n) return 1;
      break;
      }
    }
    return 0;
  }
  return 0;
}


int check_ACE_low(deck_t * hand,size_t index,suit_t fs){
  card_t perv=(*(hand->cards)[index]);
  switch (fs){
  case NUM_SUITS:
    if (perv.value==14){
      int five_idx=-1;
      for (size_t j=index+1; j<hand->n_cards;j++){
	if (hand->cards[j]->value==5){
	  five_idx=j;
	  break;
	} 	
      }
      if (five_idx!=-1){
      int check= check_straight(hand,five_idx,fs,4);
      if (check==1) return -1;
      }
    }
    break;
  default:
    if (perv.value==14 && perv.suit==fs){
      int five_idx=-1;
      for (size_t j=index+1; j<hand->n_cards;j++){
	if (hand->cards[j]->value==5){
	  five_idx=j;
	  break;
	}
      }
      if (five_idx!=-1){
      int check= check_straight(hand,five_idx,fs,4);
      if (check==1) return -1;
      }
    }
  }

  return 0;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  if (check_ACE_low(hand,index,fs)==-1) return -1;
  return check_straight(hand,index,fs,5);
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
  
  hand_eval_t ans;
  ans.ranking=what;  
  for (size_t i=idx;i<(idx+n);i++){
    ans.cards[i-idx]=hand->cards[i];
  }
  int h=n;
  for (size_t i=0; i<hand->n_cards;i++){
    if (i>=idx && i<(idx+n)) continue;
    if (h==5) break;
    ans.cards[h]=hand->cards[i];
    h++;
  }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards,hand1->n_cards,sizeof(hand1->cards[0]),card_ptr_comp);
  qsort(hand2->cards,hand2->n_cards,sizeof(hand1->cards[0]),card_ptr_comp);
  hand_eval_t h1=evaluate_hand(hand1);
  hand_eval_t h2=evaluate_hand(hand2);
  if ((int)h1.ranking- (int)h2.ranking>0){
    return -1;
  }else if ((int)h1.ranking-(int)h2.ranking<0){
    return 1;
  }else if ((int)h1.ranking-(int)h2.ranking==0){
    for (size_t i=0;i<5;i++){
      int v1=h1.cards[i]->value;
      int v2=h2.cards[i]->value;
      if (v1-v2>0){
	return 1;
      }else if (v1-v2<0) return -1;
    }
  }
  return 0;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.

unsigned * get_match_counts(deck_t * hand){
  unsigned * ans=calloc(hand->n_cards,sizeof(*ans));
  for (size_t i=0;i<hand->n_cards;i++){
    card_t h1=*hand->cards[i];
    for (size_t j=0;j<hand->n_cards;j++){
      card_t h2=*hand->cards[j];
      if (h1.value==h2.value){
	ans[i]++;
      }
    }
  }
  return ans;

}

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
