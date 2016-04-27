/*
 * cards.cpp
 *
 * 2015/01/30
 * Waheed Brown
 *
 * Blackjack
 */

#include <iostream>
#include "cards.h"
// Included in cards.h
//   #include <string>
//   using namespace std;

map<pip_t, string> Card::makePips() {
  map<pip_t, string> newPips;
  //  newPips[ACE_LOW] = "ace";
  newPips[TWO] = '2';
  newPips[THREE] = '3';
  newPips[FOUR] = '4';
  newPips[FIVE] = '5';
  newPips[SIX] = '6';
  newPips[SEVEN] = '7';
  newPips[EIGHT] = '8';
  newPips[NINE] = '9';
  newPips[TEN] = "10";
  newPips[JACK] = "jack";
  newPips[QUEEN] = "queen";
  newPips[KING] = "king";
  newPips[ACE] = "ace";
    
  return newPips;
}

map<suit_t, string> Card::makeSuits() {
  map<suit_t, string> newSuits;
  newSuits[CLUBS] = "clubs";
  newSuits[DIAMONDS] = "diamonds";
  newSuits[HEARTS] = "hearts";
  newSuits[SPADES] = "spades";
    
  return newSuits;
}

map<pip_t, string> Card::pips = Card::makePips();
map<suit_t, string> Card::suits = Card::makeSuits();

void Card::showCard() const {
  cout << '[' << Card::pips[number] << " of "
       << Card::suits[suit] << ']';
}

void Deck::showDeck() const {
  for( vector<Card>::const_iterator it = cardV.begin();
       it != cardV.end();
       ++it ) {
    it->showCard();
    cout << '\t';
  }
}
