/**
 * @file board.cpp
 * @author David Xu
 * @author Connie Yuan
 * @brief A Solitaire board
 */
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include "board.h"

namespace solitaire {
  using namespace std;

  // CardPile constructors
  CardPile::CardPile() : pile(Pile()) { }

  // CardPile constructor with a pointer to the first card and last car
  template <class InputIterator>
  CardPile::CardPile(InputIterator first, InputIterator last)
    : pile(Pile(first, last)) { }

  template <class InputIterator>
  void CardPile::Insert(Pile::iterator position, InputIterator first,
                        InputIterator last) {
    pile.insert(position, first, last);
  }

  void CardPile::PushBack(const Card& card) {
    pile.push_back(card);
  }

  void CardPile::Erase(Pile::iterator first,
                       Pile::iterator last) {
    pile.erase(first, last);
  }

  void CardPile::Erase(Pile::iterator position) {
    pile.erase(position);
  }

  Card& CardPile::Last() {
    return pile.back();
  }

  CardPile::Pile::const_iterator CardPile::Begin() const {
    return pile.begin();
  }

  CardPile::Pile::const_iterator CardPile::End() const {
    return pile.end();
  }

  CardPile::Pile::iterator CardPile::End() {
    return pile.end();
  }

  CardPile::Pile::const_reverse_iterator CardPile::REnd() const {
    return pile.rend();
  }

  bool CardPile::Empty() const {
    return pile.empty();
  }

  bool TableauPile::AllShown() const {
    return shown == Begin();
  }

  CardPile::Pile::const_iterator TableauPile::ShownBegin() const {
    return cshown;
  }

  CardPile::Pile::iterator TableauPile::ShownBegin() {
    return shown;
  }

  Suit SuitPile::GetSuit() const {
    return suit;
  }

  Board::Board(int numOpenCards) {
    Reset(numOpenCards);
  }

  void Board::Reset(int numOpenCards) {
    this->numOpenCards = numOpenCards;
    status = Status::PLAYING;
    stuckState = nullptr;
    foundation = vector<SuitPile>(kNumSuits);
    tableau = vector<TableauPile>(kTableauSize);

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
    for (int i = 0; i < kTableauSize; i++) {
      tableau[i] = TableauPile(it, next(it, i + 1));
      tableau[i].shown = prev(tableau[i].End());
      tableau[i].cshown = prev(tableau[i].End());
      advance(it, i + 1);
    }

    // make the stock cards
    deck = CardPile::Pile(it, all.end());
    stock = deck.begin();
    talon = deck.end();
  }

  bool Board::TalonEmpty() const {
    return talon == deck.end();
  }

  bool Board::StockEmpty() const {
    return stock == deck.end();
  }

  bool Board::DeckEmpty() const {
    return deck.begin() == deck.end();
  }

  Board::operator bool() const {
    return status == Status::PLAYING;
  }

  void Board::UpdateStatus() {
    if (ValidMovesInFrame()) { // valid moves exist...
      stuckState = nullptr;
      return;
    }

    // no valid moves...
    if (stuckState == nullptr) { // there were moves in prior frames but not now
      stuckState = &talon;
    } else {                     // no moves in prior frames through now
      if (*stuckState == talon) {
        status = Status::STUCK;
      }
    }

    if (all_of(tableau.begin(), tableau.end(),
               [](TableauPile tp) { return tp.Empty(); })) {
      status = Status::WON;
    }
  }

  Board::Status Board::GetStatus() const {
    return status;
  }

  template <class iterator>
  static void SafeAdvance(iterator& it, iterator end, size_t delta) {
    while (it != end && delta--) {
      ++it;
    }
  }

  template <class iterator>
  static iterator SafeNext(iterator it, iterator end, size_t delta = 1) {
    SafeAdvance(it, end, delta);
    return it;
  }


  bool Board::DoNewTalon() {
    if (deck.empty()) {
      return false;
    }

    if (stock == deck.end()) { // reached end of the stock
      talon = deck.end();
      stock = deck.begin();
    } else if (talon == deck.end()) {
      talon = deck.begin();
      stock = SafeNext(talon, deck.end(), numOpenCards);
    } else {                   // keep stock position relative to talon
      SafeAdvance(talon, deck.end(), numOpenCards);
      stock = SafeNext(talon, deck.end(), numOpenCards);
    }
    return true;
  }


  void Board::DoGetHint() {
    cout << endl;
    if (ValidMovesInFrame()) {
      cout << "There is a valid move available!";
    } else {
      cout << "There are no valid moves in this frame.";
    }
    cout << endl << endl;
  }


  /**
   * Returns true if the first card can be built down under the second card in
   * the tableau pile; otherwise, returns false.
   */
  static inline bool CanBuildDown(Card kingHigh, Card aceLow) {
    return aceLow.RankOneLessThan(kingHigh)
      && kingHigh.SuitOppositeColorFrom(aceLow);
  }

  static inline bool CanBuildDown(Card card, TableauPile tableauPile) {
    if (tableauPile.Empty() && card.IsKing()) {
      return true;
    }
    if (!tableauPile.Empty() && CanBuildDown(tableauPile.Last(), card)) {
      return true;
    }
    return false;
  }

  /**
   * Returns true if the first card can be built up above the second card in the
   * foundation pile; otherwise, returnse false.
   */
  static inline bool CanBuildUp(Card aceLow, Card kingHigh) {
    return aceLow.RankOneLessThan(kingHigh) && aceLow.SuitSameAs(kingHigh);
  }

  static inline bool CanBuildUp(Card card, SuitPile suitPile) {
    if (suitPile.Empty() && suitPile.GetSuit() == card.GetSuit()
        && card.IsAce()) {
      return true;
    }
    if (!suitPile.Empty() && CanBuildUp(suitPile.Last(), card)) {
      return true;
    }
    return false;
  }

  bool Board::DoMoveTalonToFoundation() {
    Card& talonCard = GetTalonCard();
    for (SuitPile& suitPile : foundation) {
      if (CanBuildUp(talonCard, suitPile)) {
        suitPile.PushBack(talonCard);
        CardPile::Pile::iterator position = GetTalonCardIterator();
        if (position == talon) {
          --talon;
        }
        deck.erase(position);

        UpdateStatus();
        return true;
      }
    }
    return false;
  }

  bool Board::DoMoveTableauToFoundation(Tableau::size_type tableauIdx) {
    if (tableauIdx >= tableau.size()) {
      return false;
    }
    TableauPile& tableauPile = tableau[tableauIdx];
    if (tableauPile.Empty()) {
      return false;
    }

    CardPile::Pile::iterator it = prev(tableauPile.End());
    for (SuitPile& suitPile : foundation) {
      if (CanBuildUp(*it, suitPile)) {
        suitPile.PushBack(*it);
        if (it == tableauPile.ShownBegin()
            && tableauPile.ShownBegin() != tableauPile.Begin()) {
          --tableauPile.shown;
          --tableauPile.cshown;
        }
        tableauPile.Erase(it);

        UpdateStatus();
        return true;
      }
    }
    return false;
  }

  bool Board::DoMoveTalonToTableau(Foundation::size_type tableauIdx) {
    if (tableauIdx >= tableau.size()) {
      return false;
    }
    Card& talonCard = GetTalonCard();
    if (CanBuildDown(talonCard, tableau[tableauIdx])) {
        tableau[tableauIdx].PushBack(talonCard);
        CardPile::Pile::iterator position = GetTalonCardIterator();
        if (position == talon) {
          --talon;
        }
        deck.erase(position);

        UpdateStatus();
        return true;
    }
    return false;
  }

  bool Board::DoMoveFoundationToTableau(Foundation::size_type foundationIdx,
                                        Tableau::size_type tableauIdx) {
    if (foundationIdx >= foundation.size()) {
      return false;
    }
    TableauPile& tableauPile = tableau[tableauIdx];
    SuitPile& suitPile = foundation[foundationIdx];
    if (suitPile.Empty()) {
      return false;
    }
    CardPile::Pile::iterator it = --suitPile.End();
    if (CanBuildDown(*it, tableauPile)) {
      tableauPile.PushBack(*it);
      suitPile.Erase(it);

      UpdateStatus();
      return true;
    }
    return false;
  }

  bool Board::DoMoveTableauToTableau(Tableau::size_type fromIdx,
                                     Tableau::size_type toIdx) {
    if (fromIdx == toIdx || fromIdx >= tableau.size()
        || toIdx >= tableau.size()) {
      return false;
    }

    TableauPile& fromPile = tableau[fromIdx];
    TableauPile& toPile = tableau[toIdx];
    for (CardPile::Pile::iterator it = fromPile.ShownBegin(); it != fromPile.End();
         ++it) {
      if (CanBuildDown(*it, toPile)) {
        toPile.Insert(toPile.End(), it, fromPile.End());
        if (it == fromPile.ShownBegin()
            && fromPile.ShownBegin() != fromPile.Begin()) {
          --fromPile.shown;
          --fromPile.cshown;
        }
        fromPile.Erase(it, fromPile.End());

        UpdateStatus();
        return true;
      }
    }
    return false;
  }

  Card& Board::GetTalonCard() {
    return *GetTalonCardIterator();
  }

  const Card& Board::GetTalonCard() const {
    return *GetTalonCardIterator();
  }

  CardPile::Pile::const_iterator Board::GetTalonCardIterator() const {
    return prev(stock);
  }

  CardPile::Pile::iterator Board::GetTalonCardIterator() {
    return prev(stock);
  }

  bool Board::ValidMovesInFrame() const {
    // possibile moves to the foundation...
    for (SuitPile suitPile : foundation) {
      // ...from the tableau
      for (CardPile tableauPile : tableau) {
        if (!tableauPile.Empty() &&  CanBuildUp(tableauPile.Last(), suitPile)) {
          return true;
        }

        // ... from the talon
        if (!TalonEmpty() && CanBuildUp(GetTalonCard(), suitPile)) {
          return true;
        }

      }
    }

    // possible moves to the tableau...
    for (CardPile tableauPile : tableau) {
      // ...from the tableau
      for (CardPile fromPile : tableau) {
        if (&tableauPile == &fromPile) {
          continue;
        }
        if (tableauPile.Empty() && fromPile.Last().IsKing()) {
          return true;
        } else {
          if (!tableauPile.Empty()
              && CanBuildDown(tableauPile.Last(), fromPile.Last())) {
            return true;
          }
        }
      }

      // ...from the foundation
      for (CardPile suitPile : foundation) {
        if (suitPile.Empty()) {
          continue;
        }
        if (tableauPile.Empty() && suitPile.Last().IsKing()) {
          return true;
        } else {
          if (!tableauPile.Empty()
              && CanBuildDown(tableauPile.Last(), suitPile.Last())) {
            return true;
          }
        }
      }

      // ...from the talon
      if (!TalonEmpty()) {
        if (tableauPile.Empty() && (*talon).IsKing()) {
          return true;
        } else {
          if (!tableauPile.Empty()
              && CanBuildDown(tableauPile.Last(), *talon)) {
            return true;
          }
        }
      }
    }

    return false;
  }

  void Board::DrawBoard() const {
    // Display the stock area
    if (DeckEmpty()) {
      cout << "EMPTY ";
    } else {
      cout << "STOCK ";
    }

    // Display the talon area
    if (TalonEmpty()) {
      for (int i = 0; i < numOpenCards; i++) {
        cout << "--- ";
      }
    } else {
      int n = 0;
      for (CardPile::Pile::iterator it = talon; it != stock; ++it) {
        cout << setw(2);
        (*it).Print();
        cout << " ";
        n++;
      }
      for (/**/; n < numOpenCards; n++) {
        cout << "---";
      }
    }

    cout << "    ";

    // Display the foundation area
    for (SuitPile pile : foundation) {
      if (pile.Empty()) {
        cout << "--- ";
      } else {
        setw(2);
        pile.Last().Print();
        cout << " ";
      }
    }
    cout << endl;
    cout << endl;

    // Display the tableau area
    int tableauSize = distance(tableau.begin(), tableau.end());
    vector<CardPile::Pile::const_iterator> piles;
    for (int i = 0; i < tableauSize; i++) {
      piles.push_back(tableau[i].Begin());
    }

    vector<bool> shownStatus(tableauSize);

    bool isTableauPrintingDone = true;
    do {
      isTableauPrintingDone = true;
      for (int i = 0; i < tableauSize; i++) {
        CardPile::Pile::const_iterator& cardIt = piles[i];
        if (cardIt == tableau[i].End()) {
          cout << "    ";
        } else {
          isTableauPrintingDone = false;
          if (cardIt == tableau[i].cshown) {
            shownStatus[i] = true;
          }
          if (shownStatus[i]) {
            cout << setw(2);
            (*cardIt).Print();
          } else {
            cout << "---";
          }
          cout << " ";
          ++cardIt;
        }
      }
      cout << endl;
    } while (!isTableauPrintingDone);
    cout << endl;
  }

}
