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
  // Board class (implemented below)
  class Board;

  // CardPile class to create a pile of cards
  class CardPile {
  private:
    std::list<Card> pile;
  public:
    friend class Board;

    CardPile();

    // CardPile constructor
    template <class InputIterator>
      CardPile(InputIterator first, InputIterator last);

    /**
     * Inserts the pile that starts at first and ends at last into the given
     * position.
     */
    template <class InputIterator>
      void Insert(std::list<Card>::const_iterator position, InputIterator first,
                  InputIterator last);

    /**
     * Erases the pile starting at first and ending at last.
     */
    template <class const_iterator>
      void Erase(const_iterator first, const_iterator last);
    /**
     * Returns a pointer to the last element of the pile.
     */
    Card& Last();

    /**
     * Returns an iterator that begins at the first element in the pile.
     */
    std::list<Card>::const_iterator Begin() const;

    /**
     * Returns an iterator that starts at the first position past the end of the
     * pile.
     */
    std::list<Card>::const_iterator End() const;

    /**
     * Returns an iterator that begins at the reverse end of the pile.
     */
    std::list<Card>::const_reverse_iterator REnd() const;

    /**
     * Returns whether a pile is empty.
     */
    bool Empty() const;
  };

  /**
   * TableauPile represents one stack on the tableau.
   */
  class TableauPile : public CardPile {
    friend class Board;
  private:
    std::list<Card>::const_iterator shown;
  public:
    using CardPile::CardPile;

    /**
     * Returns whether all the cards in the tableau pile are shown.
     */
    bool AllShown() const;
  };

  /**
   * SuitPile represents one stack on the foundation.
   */
  class SuitPile : public CardPile {
    friend class Board;
  private:
    Suit suit;
  public:
    using CardPile::CardPile;

    /**
     * Returns the suit of the pile.
     */
    Suit GetSuit() const;
  };

  /**
   * Board simulates the solitaire playing area.
   */
  class Board {
  public:
    enum class Status { STUCK, PLAYING, WON };
  private:
    int numOpenCards;
    mutable Status status;
    std::forward_list<Card>::iterator* stuckState;
    std::forward_list<Card>::iterator talon;
    std::forward_list<Card>::iterator stock;
    std::forward_list<Card> deck;
    std::vector<SuitPile> foundation;
    std::vector<TableauPile> tableau;

    bool ValidMovesInFrame() const;

    /**
     * Flip over three more cards to the talon.
     */
    void DoNewTalon();

    /**
     * Get a hint.
     */
    void DoGetHint();

    /**
     * Move cards.
     */
    void DoMove();

    /**
     * Updates the status of the game board accordingly.
     */
    void UpdateStatus();

  public:
    /**
     * Constructor to create a new board. The number of open cards (1 or 3) is
     * passed in.
     */
    Board(int numOpenCards = 3);

    /**
     * Resets the game board and deals a new game.
     */
    void Reset(int numOpenCards = 3);

    /**
     * Check whether the talon is empty.
     */
    bool TalonEmpty() const;

    /**
     * Check whether the stock is empty.
     */
    bool StockEmpty() const;

    /**
     * Check whether the deck is empty.
     */
    bool DeckEmpty() const;

    /**
     * Return the accessible card from the talon.
     */
    Card& GetTalonCard() const;

    enum class Play { DRAW = 1, MOVE, HINT, RESTART };

    /**
     * Perform the play action on the board.
     */
    void PerformPlay(Play play);

    /**
     * Draws the board to be displayed through the command line.
     */
    void DrawBoard() const;


    class Action;

    template <class InputIterator, class const_iterator>
      std::vector<Action> GetValidActions();

    enum class FromLocation { FOUNDATION, TABLEAU, TALON };
    enum class ToLocation { FOUNDATION, TABLEAU };

    /**
     * Returns the current status of the game.
     */
    Status GetStatus() const;

    /**
     * Returns true only if the game has not ended.
     */
    operator bool() const;
  };
}
