/**
 * @file card.cpp
 * @author David Xu
 * @author Connie Yuan
 * @brief Models a playing card.
 */
#include "card.h"

namespace solitaire {
  using namespace std;

  int IntOf(Rank rank) {
    return static_cast<int>(rank);
  }

  int IntOf(Suit suit) {
    return static_cast<int>(suit);
  }

  Card::Card(Rank rank, Suit suit)
    : rank(rank),
      suit(suit) { }

  Rank Card::GetRank() const {
    return rank;
  }

  Suit Card::GetSuit() const {
    return suit;
  }

  string StringOf(Rank rank) {
    return (string []) { "A", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
        "J", "Q", "K" }[IntOf(rank)];
  }

  string StringOf(Suit suit) {
    return (string []) { "♠", "♥", "♣", "♦" }[IntOf(suit)];
  }

  void Card::Print(ostream& out) const {
    out << StringOf(rank) << StringOf(suit);
  }

  bool Card::RankLessThan(Card card) const {
    return IntOf(rank) < IntOf(card.rank);
  }

  bool Card::SuitDifferentFrom(Card card) const {
    return IntOf(suit) < IntOf(card.suit);
  }

  bool Card::IsKing() const {
    return GetRank() == Rank::_K;
  }

  bool Card::IsAce() const {
    return GetRank() == Rank::_A;
  }

}
