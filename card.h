/**
 * @file card.h
 * @author David Xu
 * @author Connie Yuan
 * @brief Models a playing card.
 */
#pragma once
#include <iostream>
#include <list>
#include <ostream>
#include <string>
#include <vector>

#define DECK_SIZE 52
#define NUM_SUITS 4

namespace solitaire {
  enum class Rank { _A = 1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _J, _Q, _K };
  enum class Suit { SPADES, HEARTS, CLUBS, DIAMONDS };

  class Card {
  private:
    Rank rank;
    Suit suit;

  public:
    /**
     * Creates a card of the given rank and suit.
     */
    Card(Rank rank, Suit suit);

    /**
     * Returns the rank.
     */
    Rank GetRank() const;

    /**
     * Returns the suit.
     */
    Suit GetSuit() const;

    /**
     * Prints the information of a card.
     */
    void Print(std::ostream& out = std::cout) const;

    /**
     * Compares the ranks of two cards.
     */
    bool RankLessThan(Card card) const;

    /**
     * Compares the suit of two cards.
     */
    bool SuitDifferentFrom(Card card) const;

    /**
     * Returns whether the card is a king.
     */
    bool IsKing() const;

    /**
     * Returns whether the card is an ace.
     */
    bool IsAce() const;
  };

  /**
   * Returns the integer behind the rank enum.
   */
  int IntOf(Rank rank);

  /**
   * Returns the integer behind the suit enum.
   */
  int IntOf(Suit suit);

  /**
   * Given a rank, return the string of the letter of the card.
   */
  std::string StringOf(Rank rank);

  /**
   * Given a suit, return the string of the character of the suit.
   */
  std::string StringOf(Suit suit);



}
