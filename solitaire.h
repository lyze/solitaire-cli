/**
 * @file solitaire.h
 * @author David Xu
 * @author Connie Yuan
 * @brief Prototypes of functions relevant to the card game Solitaire.
 */
#pragma once
#include "board.h"

namespace solitaire {
  const int kOneCardGame = 1;
  const int kThreeCardGame = 3;

  /**
   * Display the welcome message and prompt user for type of game (one-card or
   * three-card). Returns the number of cards to use in the game.
   */
  int SetupGame();

  enum class Play { TALON = 1, MOVE, HINT, RESTART };

  enum class Move { TALON_TO_FOUNDATION = 1, TABLEAU_TO_FOUNDATION,
      TALON_TO_TABLEAU, TABLEAU_TO_TABLEAU, FOUNDATION_TO_TABLEAU };

  /**
   * Display playing options and prompt user to enter choice. Returns the play
   * if valid.
   */
  Play GetPlay();

  void DoPlay(Board& game, Play playOption);

  void DoMove(Board& game, Move moveOption);

}
