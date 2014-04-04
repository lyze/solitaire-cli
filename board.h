/**
 * @file board.h
 * @author David Xu
 * @author Connie Yuan
 * @brief A Solitaire board.
 */
#pragma once
#include <iterator>
#include <forward_list>
#include <vector>
#include "card.h"

#define TABLEAU_SIZE 7

namespace solitaire {

  class Board {
  private:
    int numOpenCards;
    std::forward_list<Card>::iterator talon;
    std::forward_list<Card>::iterator stock; // never points to end unless empty
    std::forward_list<Card> deck;
    std::vector<CardPile> foundation;
    std::vector<CardPile> tableau;

  public:
    Board(int numOpenCards = 3);
    bool IsTalonEmpty();
    bool IsStockEmpty();
    bool IsDeckEmpty();
    Board& MoveTalonToFoundation(Suit suit);
    void DrawBoard();
    // TODO: use internal bitflag state
    // TODO: override operator void*() const
    // TODO: override operator!() const

  };

}
