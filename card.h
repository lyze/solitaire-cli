/**
 * @file card.h
 * @author David Xu
 * @author Connie Yuan
 * @brief Models a playing card.
 */
#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#define DECK_SIZE 52

namespace solitaire {
  enum class Rank { _A = 1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _J, _Q, _K };

  enum class Suit { SPADES, HEARTS, CLUBS, DIAMONDS };

  class Card {
  private:
    Rank rank;
    Suit suit;

  public:
    Card(Rank rank, Suit suit);

    Rank GetRank();
    Suit GetSuit();

    void Print(std::ostream& out = std::cout);
    bool RankLessThan(Card card);
    bool SuitDifferentFrom(Card card);


  };

  int IntOf(Rank rank);

  int IntOf(Suit suit);

  typedef std::vector<Card> CardPile;

}
