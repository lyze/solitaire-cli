/**
 * @file board.cpp
 * @author David Xu
 * @author Connie Yuan
 * @brief A Solitaire board
 */
#include <algorithm>
#include "board.h"

namespace solitaire {
  using namespace std;

  Board::Board(int numOpenCards)
    : numOpenCards(numOpenCards),
      deck ({ Card(Rank::_A, Suit::SPADES), Card(Rank::_2, Suit::SPADES),
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
            Card(Rank::_Q, Suit::DIAMONDS), Card(Rank::_K, Suit::DIAMONDS) }),
    foundation(IntOf(Suit::DIAMONDS), CardPile()),
    tableau(TABLEAU_SIZE, CardPile()) {

    random_shuffle(deck.begin(), deck.end());
    closed = deck.begin();
    opened = deck.end();
  }

}
