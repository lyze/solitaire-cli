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

  class Board;

  class CardPile {
  private:
    std::list<Card> pile;
  public:
    friend class Board;
    CardPile();

    template <class InputIterator>
      CardPile(InputIterator first, InputIterator last);

    template <class InputIterator>
      void Insert(std::list<Card>::const_iterator position, InputIterator first,
                  InputIterator last);

    template <class const_iterator>
      void Erase(const_iterator first, const_iterator last);

    Card& Last();
    std::list<Card>::const_iterator Begin() const;
    std::list<Card>::const_iterator End() const;
    std::list<Card>::const_reverse_iterator REnd() const;
    bool Empty() const;
  };

  class TableauPile : public CardPile {
    friend class Board;
  private:
    std::list<Card>::const_iterator shown;
  public:
    using CardPile::CardPile;
    bool AllShown() const;
  };

  class SuitPile : public CardPile {
    friend class Board;
  private:
    Suit suit;
  public:
    using CardPile::CardPile;
    Suit GetSuit() const;
  };

  class Board {
  public:
    enum class Status { STUCK, PLAYING, WON };
  private:
    int numOpenCards;
    Status status;
    std::forward_list<Card>::iterator talon;
    std::forward_list<Card>::iterator stock;
    std::forward_list<Card> deck;
    std::vector<SuitPile> foundation;
    std::vector<TableauPile> tableau;
    void UpdateStatus();

  public:
    Board(int numOpenCards = 3);

    bool TalonEmpty() const;
    bool StockEmpty() const;
    bool DeckEmpty() const;

    void DrawBoard() const;

    class Action;

    template <class InputIterator, class const_iterator>
      std::vector<Action> GetValidActions();

    enum class FromLocation { FOUNDATION, TABLEAU, TALON };
    enum class ToLocation { FOUNDATION, TABLEAU };
    Status GetStatus() const;
    operator bool() const;
  };
}
