/**
 * @file card.cpp
 * @author David Xu
 * @author Connie Yuan
 * @brief Models a playing card.
 */
#include "card.h"

using namespace solitaire;

Card::Card(Rank rank, Suit suit)
  : rank(rank),
    suit(suit) {}
