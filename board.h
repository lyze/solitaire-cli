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
  private:
    int numOpenCards;
    struct status;
    std::forward_list<Card>::iterator talon;
    std::forward_list<Card>::iterator stock;
    std::forward_list<Card> deck;
    std::vector<SuitPile> foundation;
    std::vector<TableauPile> tableau;

  public:
    Board(int numOpenCards = 3);

    bool TalonEmpty() const;
    bool StockEmpty() const;
    bool DeckEmpty() const;

    void MoveTalonToFoundation(Suit suit);

    enum class FromLocation { FOUNDATION, TABLEAU, TALON };
    enum class ToLocation { FOUNDATION, TABLEAU };

    class Action {
    public:
      virtual bool DoAction() = 0;
    };

    class TurnOverTableauCard : public Action {
    private:
      TableauPile& pile;
    public:
      TurnOverTableauCard(TableauPile& pile);
      bool DoAction();
    };

    class TurnOverTalon : public Action {
    private:
      Board& board;
    public:
      TurnOverTalon(Board& board);
      bool DoAction();
    };

    template <class InputIterator, class const_iterator>
      class Move : public Action {
    private:
      const FromLocation fromLocation;
      const CardPile& from;
      const ToLocation toLocation;
      const CardPile& to;
      const InputIterator begin;
      const InputIterator end;
      const const_iterator position;
    public:
      Move(FromLocation fromLocation, CardPile& from, InputIterator begin,
           InputIterator end, ToLocation toLocation, CardPile& to,
           const_iterator position);
      bool DoAction() = 0;
    };

    template <class InputIterator, class const_iterator>
      std::vector<Action> GetValidMoves();

  };

}
