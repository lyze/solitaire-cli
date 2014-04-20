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

namespace solitaire {
  const int kTableauSize = 7;

  // forward declaration
  class Board;

  class CardPile {
  private:
    std::list<Card> pile;

  public:
    typedef std::list<Card> Pile;

    /**
     * Initializes a pile of cards with nothing in it.
     */
    CardPile();

    /**
     * Initializes a pile of cards from the range provided.
     */
    template <class InputIterator>
      CardPile(InputIterator first, InputIterator last);

    /**
     * Inserts the pile that starts at first and ends at last into the given
     * position.
     */
    template <class InputIterator>
      void Insert(Pile::iterator position, InputIterator first,
                  InputIterator last);

    /**
     * Inserts the card at the end
     */
    void PushBack(const Card& card);

    /**
     * Erases the cards starting at first and ending at last.
     */
    void Erase(Pile::iterator first, Pile::iterator last);

    /**
     * Erases the card at the position.
     */
    void Erase(Pile::iterator position);

    /**
     * Returns a pointer to the last element of the pile.
     */
    Card& Last();

    /**
     * Returns an iterator that begins at the first element in the pile.
     */
    Pile::const_iterator Begin() const;

    /**
     * Returns an iterator that starts at the first position past the end of the
     * pile.
     */
    Pile::const_iterator End() const;

    /**
     * Returns an iterator that starts at the first position past the end of the
     * pile.
     */
    Pile::iterator End();

    /**
     * Returns an iterator that begins at the reverse end of the pile.
     */
    Pile::const_reverse_iterator REnd() const;

    /**
     * Returns whether a pile is empty.
     */
    bool Empty() const;
  };

  /**
   * TableauPile represents one stack on the tableau.
   */
  class TableauPile : public CardPile {
  private:
    /**
     * A board should be able to manage the card piles in play.
     */
    friend class Board;
    Pile::const_iterator cshown;
    Pile::iterator shown;

  public:
    using CardPile::CardPile;

    /**
     * Returns whether all the cards in the tableau pile are shown.
     */
    bool AllShown() const;

    /**
     * Returns an iterator to the first face-up card in the pile.
     */
    Pile::const_iterator ShownBegin() const;

    /**
     * Returns an iterator to the first face-up card in the pile.
     */
    Pile::iterator ShownBegin();
  };

  /**
   * SuitPile represents one stack on the foundation.
   */
  class SuitPile : public CardPile {
  private:
    /**
     * A board should be able to manage the card piles in play.
     */
    friend class Board;

    /**
     * The suit of all cards in this pile.
     */
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
    typedef std::vector<SuitPile> Foundation;
    typedef std::vector<TableauPile> Tableau;

    int numOpenCards;
    mutable Status status;
    CardPile::Pile::iterator* stuckState;
    CardPile::Pile::iterator talon;
    CardPile::Pile::iterator stock;
    CardPile::Pile deck;
    Foundation foundation;
    Tableau tableau;

    /**
     * Returns true if there are valid moves to play in the current frame;
     * otherwise, returns false.
     */
    bool ValidMovesInFrame() const;

    /**
     * Updates the status of the game board accordingly.
     */
    void UpdateStatus();

  public:
    /**
     * Creates a new board, given the number of open cards for the talon.
     */
    Board(int numOpenCards = 3);

    /**
     * Resets the game board and deals a new game.
     */
    void Reset(int numOpenCards = 3);

    /**
     * Checks whether the talon is empty.
     */
    bool TalonEmpty() const;

    /**
     * Checks whether the stock is empty.
     */
    bool StockEmpty() const;

    /**
     * Checks whether the deck is empty.
     */
    bool DeckEmpty() const;

    /**
     * Returns the accessible card from the talon.
     */
    Card& GetTalonCard();

    /**
     * Returns the accessible card from the talon.
     */
    const Card& GetTalonCard() const;

    /**
     * Returns an iterator to the accessible talon card.
     */
    CardPile::Pile::const_iterator GetTalonCardIterator() const;

    /**
     * Returns an iterator to the accessible talon card.
     */
    CardPile::Pile::iterator GetTalonCardIterator();

    /**
     * Flip over three more cards to the talon.
     */
    bool DoNewTalon();

    /**
     * Get a hint.
     */
    void DoGetHint();

    /**
     * Move the talon card to the foundation.
     */
    bool DoMoveTalonToFoundation();

    /**
     * Move the card(s) from the tableau to the foundation.
     */
    bool DoMoveTableauToFoundation(Tableau::size_type tableauIdx);

    /**
     * Move the talon card to the tableau.
     */
    bool DoMoveTalonToTableau(Tableau::size_type tableauIdx);

    /**
     * Move the card from the foundation pile to the tableau pile.
     */
    bool DoMoveFoundationToTableau(Foundation::size_type foundationIdx,
                                   Tableau::size_type tableauIdx);

    /**
     * Move the card(s) from the source tableau pile to the destination tableau
     * pile.
     */
    bool DoMoveTableauToTableau(Tableau::size_type fromIdx,
                                Tableau::size_type toIdx);

    /**
     * Draws the board to be displayed through the command line.
     */
    void DrawBoard() const;

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
