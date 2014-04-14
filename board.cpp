/**
 * @file board.cpp
 * @author David Xu
 * @author Connie Yuan
 * @brief A Solitaire board
 */
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <string>
#include "board.h"

namespace solitaire {
  using namespace std;

  // CardPile constructors
  CardPile::CardPile() : pile(list<Card>()) { }

  // CardPile constructor with a pointer to the first card and last car
  template <class InputIterator>
  CardPile::CardPile(InputIterator first, InputIterator last)
    : pile(list<Card>(first, last)) { }

  // Inserts the pile that starts at first and ends at last into position
  template <class InputIterator>
  void CardPile::Insert(list<Card>::const_iterator position,
                        InputIterator first, InputIterator last) {
    pile.insert(position, first, last);
  }

  // Erases the pile starting at first and ending at last
  template <class const_iterator>
  void CardPile::Erase(const_iterator first, const_iterator last) {
    pile.erase(first, last);
  }

  // Returns a pointer to the last element of the pile
  Card& CardPile::Last() {
    return pile.back();
  }

  // Returns an iterator that begins at the first element in the pile
  list<Card>::const_iterator CardPile::Begin() const {
    return pile.begin();
  }

  // Returns an iterator that starts at the first position past the pile's end
  list<Card>::const_iterator CardPile::End() const {
    return pile.end();
  }

  // Returns an iterator that begins at the reverse end of the pile
  list<Card>::const_reverse_iterator CardPile::REnd() const {
    return pile.rend();
  }

  // Returns whether a pile is empty
  bool CardPile::Empty() const {
    return pile.empty();
  }

  // Returns whether all the cards in the tableau pile are shown
  bool TableauPile::AllShown() const {
    return shown == Begin();
  }

  // Returns the suit of the pile
  Suit SuitPile::GetSuit() const {
    return suit;
  }

  /* Constructor to create a new board. The number of open 
     cards (1 or 3) is passed in.
  */
  Board::Board(int numOpenCards)
    : numOpenCards(numOpenCards),
      foundation(NUM_SUITS + 1, SuitPile()),
      tableau(TABLEAU_SIZE, TableauPile()) {

    // Creates a vector of all the cards in a deck
    vector<Card> all = {
      Card(Rank::_A, Suit::SPADES), Card(Rank::_2, Suit::SPADES),
      Card(Rank::_3, Suit::SPADES), Card(Rank::_4, Suit::SPADES),
      Card(Rank::_5, Suit::SPADES), Card(Rank::_6, Suit::SPADES),
      Card(Rank::_7, Suit::SPADES), Card(Rank::_8, Suit::SPADES),
      Card(Rank::_9, Suit::SPADES), Card(Rank::_10, Suit::SPADES),
      Card(Rank::_J, Suit::SPADES), Card(Rank::_Q, Suit::SPADES),
      Card(Rank::_K, Suit::SPADES), Card(Rank::_A, Suit::HEARTS),
      Card(Rank::_2, Suit::HEARTS), Card(Rank::_3, Suit::HEARTS),
      Card(Rank::_4, Suit::HEARTS), Card(Rank::_5, Suit::HEARTS),
      Card(Rank::_6, Suit::HEARTS), Card(Rank::_7, Suit::HEARTS),
      Card(Rank::_8, Suit::HEARTS), Card(Rank::_9, Suit::HEARTS),
      Card(Rank::_10, Suit::HEARTS), Card(Rank::_J, Suit::HEARTS),
      Card(Rank::_Q, Suit::HEARTS), Card(Rank::_K, Suit::HEARTS),
      Card(Rank::_A, Suit::CLUBS), Card(Rank::_2, Suit::CLUBS),
      Card(Rank::_3, Suit::CLUBS), Card(Rank::_4, Suit::CLUBS),
      Card(Rank::_5, Suit::CLUBS), Card(Rank::_6, Suit::CLUBS),
      Card(Rank::_7, Suit::CLUBS), Card(Rank::_8, Suit::CLUBS),
      Card(Rank::_9, Suit::CLUBS), Card(Rank::_10, Suit::CLUBS),
      Card(Rank::_J, Suit::CLUBS), Card(Rank::_Q, Suit::CLUBS),
      Card(Rank::_K, Suit::CLUBS), Card(Rank::_A, Suit::DIAMONDS),
      Card(Rank::_2, Suit::DIAMONDS), Card(Rank::_3, Suit::DIAMONDS),
      Card(Rank::_4, Suit::DIAMONDS), Card(Rank::_5, Suit::DIAMONDS),
      Card(Rank::_6, Suit::DIAMONDS), Card(Rank::_7, Suit::DIAMONDS),
      Card(Rank::_8, Suit::DIAMONDS), Card(Rank::_9, Suit::DIAMONDS),
      Card(Rank::_10, Suit::DIAMONDS), Card(Rank::_J, Suit::DIAMONDS),
      Card(Rank::_Q, Suit::DIAMONDS), Card(Rank::_K, Suit::DIAMONDS) };

    // Creates a random shuffle to begin a new game
    srand(time(nullptr));
    random_shuffle(all.begin(), all.end(), [](int i) -> int
                   { return rand() % i; });

    // make the tableau
    vector<Card>::iterator it = all.begin();
    for (int i = 0; i < TABLEAU_SIZE; i++) {
      tableau[i] = TableauPile(it, next(it, i + 1));
      tableau[i].shown = prev(tableau[i].End());
      advance(it, i + 1);
    }

    // make the stock cards
    deck = forward_list<Card>(it, all.end());
    stock = deck.begin();
    talon = deck.end();
    UpdateStatus();
  }

  // Check whether the talon is empty
  bool Board::TalonEmpty() const {
    return talon == deck.end();
  }

  // Check whether the stock is empty
  bool Board::StockEmpty() const {
    return stock == deck.end();
  }

  // Check whether the deck is empty
  bool Board::DeckEmpty() const {
    return deck.begin() == deck.end();
  }

  // Returns true only if the game has not ended
  Board::operator bool() const {
    return status != Status::PLAYING;
  }

  
  // Updates the status of the game board accordingly.
  void Board::UpdateStatus() {
    // TODO
    // Update status if stuck.
  }

  // Returns the current status of the game
  Board::Status Board::GetStatus() const {
    return status;
  }

  // Draws the board to be displayed through the command line
  void Board::DrawBoard() const {
    //Display the stock area
    if (DeckEmpty()) {
      cout << "EMPTY ";
    } else {
      cout << "STOCK ";
    }

    // Display the talon area
    if (TalonEmpty()) {
      for (int i = 0; i < numOpenCards; i++) {
        cout << "-- ";
      }
    } else {
      int n = 0;
      for (forward_list<Card>::iterator it = talon; talon != stock; next(it)) {
        (*it).Print();
        n++;
      }
      for (/**/; n < numOpenCards; n++) {
        cout << "--";
      }
    }

    cout << "    ";
    
    // Display the foundation area
    for (SuitPile pile : foundation) {
      if (pile.Empty()) {
        cout << "-- ";
      } else {
        pile.Last().Print();
      }
    }
    cout << endl;

    // Display the tableau area
    int tableauSize = distance(tableau.begin(), tableau.end());
    vector<list<Card>::const_iterator> piles;
    for (int i = 0; i < tableauSize; i++) {
      piles.push_back(tableau[i].Begin());
    }

    bool isTableauPrintingDone = true;
    do {
      isTableauPrintingDone = true;
      for (int i = 0; i < tableauSize; i++) {
        list<Card>::const_iterator& cardIt = piles[i];
        if (cardIt == tableau[i].End()) {
          cout << "   ";
        } else {
          isTableauPrintingDone = false;
          if (distance(cardIt, tableau[i].shown) > 0) {
            cout << "--";
          } else {
            (*cardIt).Print();
          }
          cout << " ";
          ++cardIt;
        }
      }
      cout << endl;
    } while (!isTableauPrintingDone);
    cout << endl;
  }


  /**
   * Returns true if the first card can be built down under the second card in
   * the tableau pile; otherwise, returns false.
   */
  static inline bool CanBuildDown(Card kingHigh, Card aceLow) {
    return aceLow.RankLessThan(kingHigh) && kingHigh.SuitDifferentFrom(aceLow);
  }

  /**
   * Returns true if the first card can be built up above the second card in the
   * foundation pile; otherwise, returnse false.
   */
  static inline bool CanBuildUp(Card aceLow, Card kingHigh) {
    return aceLow.RankLessThan(kingHigh) && !aceLow.SuitDifferentFrom(kingHigh);
  }


  //TODO
  /*
  Board::TurnOverTableauCard::TurnOverTableauCard(TableauPile& pile)
    : pile(pile) { }

  bool Board::TurnOverTableauCard::DoAction() {
    if (pile.Empty() || pile.AllShown()) {
      return false;
    }
    pile.shown = prev(pile.shown);
    return true;
  }

  Board::TurnOverTalon::TurnOverTalon(Board& board) : board(board) { };

  bool Board::TurnOverTalon::DoAction() {
    if (board.DeckEmpty()) {
      return false;
    }
    board.talon = board.stock;
    if (board.StockEmpty()) {
      board.stock = board.deck.begin();
    }
    board.stock = next(board.stock, board.numOpenCards);
    return true;
  }

  template <class InputIterator, class const_iterator>
  Board::Move<InputIterator, const_iterator>
  ::Move(FromLocation fromLocation, CardPile& from, InputIterator begin,
         InputIterator end, ToLocation toLocation, CardPile& to,
         const_iterator position)
    : fromLocation(fromLocation),
      from(from),
      toLocation(toLocation),
      to(to),
      begin(begin),
      end(end),
      position(position) { }

  template <class InputIterator, class const_iterator>
  bool Board::Move<InputIterator, const_iterator>::DoAction() {
    switch (fromLocation) {
    case FromLocation::TABLEAU:
      if (end != from.End()) {
        return false;
      }
      break;
    case FromLocation::FOUNDATION:
      if (next(begin) != end) {
        return false;
      }
      break;
    case FromLocation::TALON:
      if (next(begin) != end) {
        return false;
      }
      break;
    default:
      string n = static_cast<int>(toLocation);
      throw logic_error("Move::DoAction: Unknown enum value (" + n + ")");
    }
    switch (toLocation) {
    case ToLocation::TABLEAU:
      if (!CanBuildDown(*prev(position), *begin)) {
        return false;
      }
      break;
    case ToLocation::FOUNDATION:
      if (!CanBuildUp(*prev(position), *begin)) {
        return false;
      }
      break;
    default:
      string n = static_cast<int>(toLocation);
      throw logic_error("Move::DoAction: Unknown enum value (" + n + ")");
    }
    to.Insert(position, begin, end);
    from.Erase(begin, end);
    return true;
  }

  template <class InputIterator, class const_iterator>
  vector<Board::Action> Board::GetValidActions() {
    typedef Move<InputIterator, const_iterator> Move;
    vector<Action> actions;

    // possible moves to the foundation...
    for (SuitPile& suitPile : foundation) {
      // ...from the talon
      if (!TalonEmpty()) {
        if (suitPile.Empty()
            && suitPile.GetSuit() == (*talon).GetSuit() && (*talon).IsAce()) {
          Move move(FromLocation::TALON, deck, talon, next(talon),
                    ToLocation::FOUNDATION, suitPile, suitPile.End());
          actions.push_back(move);
        } else {
          if (CanBuildUp(suitPile.Last(), *talon)) {
            Move move(FromLocation::TALON, deck, talon, next(talon),
                      ToLocation::FOUNDATION, suitPile, suitPile.End());
            actions.push_back(move);
          }
        }
      }
      // ...from the tableau
      for (CardPile& tableauPile : tableau) {
        if (!tableauPile.Empty()) {
          if (suitPile.Empty()
              && suitPile.GetSuit() == tableauPile.Last().GetSuit()
              && tableauPile.Last().IsAce()) {
            Move move(FromLocation::TABLEAU, tableauPile, tableauPile.Last(),
                      tableauPile.End(), ToLocation::FOUNDATION, suitPile,
                      suitPile.End());
            actions.push_back(move);
          } else {
            if (CanBuildUp(suitPile.Last(), tableauPile.Last())) {
              Move move(FromLocation::TABLEAU, tableauPile, tableauPile.Last(),
                        tableauPile.End(), ToLocation::FOUNDATION, suitPile,
                        suitPile.End());
              actions.push_back(move);
            }
          }
        }
      }
    }

    // FIXME: remove duplicated logic

    // possible moves to the tableau...
    for (CardPile& tableauPile : tableau) {
      // ...from the tableau
      for (CardPile& fromPile : tableau) {
        if (&tableauPile == &fromPile) {
          continue;
        }
        if (tableauPile.Empty() && fromPile.Last().IsKing()) {
          Move move(FromLocation::TABLEAU, fromPile, fromPile.Last(),
                    fromPile.End(), ToLocation::TABLEAU, tableauPile,
                    tableauPile.End());
          actions.push_back(move);
        } else {
          if (!tableauPile.Empty()
              && CanBuildDown(tableauPile.Last(), fromPile.Last())) {
            Move move(FromLocation::TABLEAU, fromPile, fromPile.Last(),
                      fromPile.End(), ToLocation::TABLEAU, tableauPile,
                      tableauPile.End());
            actions.push_back(move);
          }
        }
      }

      // ...from the foundation
      for (CardPile& suitPile : foundation) {
        if (suitPile.Empty()) {
          continue;
        }
        if (tableauPile.Empty() && suitPile.Last().IsKing()) {
          Move move(FromLocation::FOUNDATION, foundation, suitPile.Last(),
                    suitPile.End(), ToLocation::TABLEAU, tableauPile,
                    tableauPile.End());
          actions.push_back(move);
        } else {
          if (!tableauPile.Empty()
              && CanBuildDown(tableauPile.Last(), suitPile.Last())) {
            Move move(FromLocation::FOUNDATION, foundation, suitPile.Last(),
                      suitPile.End(), ToLocation::TABLEAU, tableauPile,
                      tableauPile.End());
            actions.push_back(move);
          }
        }
      }

      // ...from the talon
      if (!TalonEmpty()) {
        if (tableauPile.Empty() && (*talon).IsKing()) {
          Move move(FromLocation::TALON, deck, talon, next(talon),
                    ToLocation::TABLEAU, tableauPile, tableauPile.End());
          actions.push_back(move);
        } else {
          if (!tableauPile.Empty()
              && CanBuildDown(tableauPile.Last(), *talon)) {
            Move move(FromLocation::TALON, deck, talon, next(talon),
                      ToLocation::TABLEAU, tableauPile, tableauPile.End());
            actions.push_back(move);
          }
        }
      }
    }

    // reveal next talon
    // TODO


    // RETURN
    return actions;
  }
  */

}
