/*
 * cards.h
 *
 * 2015/01/30
 * Waheed Brown
 *
 * Final Project
 */

#include <vector>
#include <map>
#include <string>
using namespace std;

enum suit_t {CLUBS, DIAMONDS, HEARTS, SPADES};
enum pip_t {ACE_LOW = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6,
	    SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, JACK = 110,
	    QUEEN = 210, KING = 310, ACE = 11};

class Card {
private:
  suit_t suit;
  // (bug 11) Change pips map<int, string> to unordered_map<int, string>
  pip_t number;
  // (bug 13) Make a Card Class Member Called faceUp so Bank Cards are hidden
  static map<pip_t, string> makePips();
  static map<suit_t, string> makeSuits();

public:
  static map<suit_t, string> suits;
  static map<pip_t, string> pips;
  Card() {}
  Card(const suit_t newSuit, const pip_t newNumber) :
    suit(newSuit), number(newNumber) {}
  const suit_t *getSuit() const { return &suit; }
  const pip_t *getNumber() const { return &number; }
  void setSuit(const suit_t newSuit) { suit = newSuit; }
  void setNumber(const pip_t newNumber) { number = newNumber; }
  void showCard() const;
};

class Deck {
 private:
  vector<Card> cardV;

public:
  Deck() {}
  vector<Card> &getList() { return cardV; }
  void showDeck() const;
};
