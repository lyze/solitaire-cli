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
      void Insert(std::list<Card>::iterator position, InputIterator first,
                  InputIterator last);

    /**
     * Inserts the card at the end
     */
    void PushBack(const Card& card);

    /**
     * Erases the cards starting at first and ending at last.
     */
    void Erase(std::list<Card>::iterator first,
               std::list<Card>::iterator last);

    /**
     * Erases the card at the position.
     */
    void Erase(std::list<Card>::iterator position);

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
     * Returns an iterator that starts at the first position past the end of the
     * pile.
     */
    std::list<Card>::iterator End();

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
    std::list<Card>::const_iterator cshown;
    std::list<Card>::iterator shown;
  public:
    using CardPile::CardPile;

    /**
     * Returns whether all the cards in the tableau pile are shown.
     */
    bool AllShown() const;

    std::list<Card>::const_iterator ShownBegin() const;
    std::list<Card>::iterator ShownBegin();
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
    std::list<Card>::iterator* stuckState;
    std::list<Card>::iterator talon;
    std::list<Card>::iterator stock;
    std::list<Card> deck;
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
    void DoMove(int fromN, int toN, int fromIdx, int toIdx);

    /**
     * Move the talon card to the foundation.
     */
    bool DoMoveTalonToFoundation();

    /**
     * Move the card(s) from the tableau to the foundation.
     */
    bool DoMoveTableauToFoundation(int idx);

    /**
     * Move the talon card to the tableau.
     */
    bool DoMoveTalonToTableau(int idx);

    /**
     * Move the card from the foundation pile to the tableau pile.
     */
    bool DoMoveFoundationToTableau(int foundationIdx, int tableauIdx);

    /**
     * Move the card(s) from the source tableau pile to the destination tableau
     * pile.
     */
    bool DoMoveTableauToTableau(int fromIdx, int toIdx);

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
    Card& GetTalonCard();

    /**
     * Return the accessible card from the talon.
     */
    const Card& GetTalonCard() const;

    /**
     * Return an iterator to the accessible talon card.
     */
    std::list<Card>::const_iterator GetTalonCardIterator() const;

    std::list<Card>::iterator GetTalonCardIterator();

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
