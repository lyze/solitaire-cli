/**
 * @file card.cpp
 * @author David Xu
 * @author Connie Yuan
 * @brief Models a playing card.
 */
#include "card.h"

namespace solitaire {
  using namespace std;

  // Returns the integer behind the rank enum
  int IntOf(Rank rank) {
    return static_cast<int>(rank);
  }

  // Returns the integer behind the suit enum
  int IntOf(Suit suit) {
    return static_cast<int>(suit);
  }

  // Constructor to create one card
  Card::Card(Rank rank, Suit suit)
    : rank(rank),
      suit(suit) { }

  // Getter method for returning the rank
  Rank Card::GetRank() const {
    return rank;
  }

  // Getter method for returning the suit
  Suit Card::GetSuit() const {
    return suit;
  }

  // Given a rank, return the string of the letter of the card
  string StringOf(Rank rank) {
    return (string []) { "A", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
        "J", "Q", "K" }[IntOf(rank)];
  }

  // Given a suit, return the string of the character of the suit
  string StringOf(Suit suit) {
    return (string []) { "♠", "♥", "♣", "♦" }[IntOf(suit)];
  }

  // Prints the information of a card
  void Card::Print(ostream& out) const {
    out << StringOf(rank) << StringOf(suit);
  }

  // Compares the ranks of two cards
  bool Card::RankLessThan(Card card) const {
    return IntOf(rank) < IntOf(card.rank);
  }

  // Compares the suit of two cards
  bool Card::SuitDifferentFrom(Card card) const {
    return IntOf(suit) < IntOf(card.suit);
  }

  // Returns whether card is king
  bool Card::IsKing() const {
    return GetRank() == Rank::_K;
  }

  // Returns whether card is ace
  bool Card::IsAce() const {
    return GetRank() == Rank::_A;
  }

}
