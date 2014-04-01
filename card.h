/**
 * @file card.h
 * @author David Xu
 * @author Connie Yuan
 * @brief Models a playing card.
 */
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

namespace solitaire {
  enum class Rank { _A = 1,  _2, _3, _4, _5, _6, _7, _8, _9, _10, _J, _Q, _K };

  enum class Suit { SPADE, HEART, CLUBS, DIAMOND };

  class Card {
  public:
    const Rank rank;
    const Suit suit;

    Card(Rank rank, Suit suit);

    void Print(std::ostream& out = std::cout);
    bool RankLessThan();
    bool SuitDifferentFrom();
  };

  typedef std::vector<Card> CardPile;

}
