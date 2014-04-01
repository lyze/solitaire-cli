/**
 * @file board.h
 * @author David Xu
 * @author Connie Yuan
 * @brief A Solitaire board.
 */
#include <vector>
#include "card.h"

namespace solitaire {
  class Board {
  private:
    const vector<CardPile> foundation;
  public:
    const int numOpenCards;
    Board(int numOpenCards = 3);
  }
}
