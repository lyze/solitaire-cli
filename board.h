/**
 * @file board.h
 * @author David Xu
 * @author Connie Yuan
 * @brief A Solitaire board.
 */
#pragma once
#include <iterator>
#include <vector>
#include "card.h"

#define TABLEAU_SIZE 7

namespace solitaire {

  class Board {
  private:
    int numOpenCards;
    std::vector<Card>::iterator opened;
    std::vector<Card>::iterator closed;
    std::vector<Card> deck;
    std::vector<CardPile> foundation;
    std::vector<CardPile> tableau;

  public:
    Board(int numOpenCards = 3);
  };

}
