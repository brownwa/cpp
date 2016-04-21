/*
 * game.h
 *
 * 2015/1/28
 * Waheed Brown
 *
 * Final Project
 * MIT6_096IAP11_project.pdf
 */

#include <map>
#include <exception>
#include "cards.h"
// Included in cards.h
//   #include <string>
//   #include <vector>
//   using namespace std;

// Just use the Deck class to be a player's hand

class Player {
 private:
  string name;
  vector<Card> hand;
  int score;

 public:
  Player() {}
 Player(const string newName) : name(newName) {}
  Player(const Player &p);
  const string &getName() const { return name; }
  void setName(const string newName) { name = newName; }
  const int getScore() const { return score; }
  void setScore(const int newScore) { score = newScore; }
  vector<Card> &getHand() { return hand; }
  void showHand() const;
  void hit(const Card newCard) { hand.push_back(newCard); }
  const int calcHand() const;
  void clearHand() { hand.clear(); }
};

class Game {
 private:
  static int numGames;
  int numPlayers;
  Player *playerList;
  Deck gameDeck;

 public:
  Game(const int newPlayers);
  ~Game();
  const int getNumPlayers() const { return numPlayers; }
  void addPlayer(const string playerName);
  void showPlayers() const;
  void buildDeck();
  // (bug 12) Shuffle the deck before dealing
  //void shuffleDeck();
  void dealCard(const int pIndex);
  void showDeck() const { gameDeck.showDeck(); }
  void showTable() const;
  void askPlayer(const int pIndex);
  void askBank();
  void clearHand(const int pIndex) { playerList[pIndex].clearHand(); }
  void checkWinners() const;
  void playAgain(const int pIndex, int *g_newPlayers);
};

struct game_singleton_err : public exception {
  const char * what () const throw () {
    return "Game already exists";
  }
};
