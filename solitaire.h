/**
 * @file solitaire.h
 * @author David Xu
 * @author Connie Yuan
 * @brief Prototypes of functions relevant to the card game Solitaire.
 */
#pragma once
#include "board.h"

/**
 * Returns the next word from @ref cin.
 */
std::string GetString();

/**
 * Gets the next int value from @ref cin.
 */
int GetInt();

/**
 * Gets a valid option value from @ref cin in the range @p min and @p max,
 * inclusive. The template parameter @p OptionRangeType must be convertible to
 * and from an int with @c static_cast.
 */
template <typename OptionRangeType>
OptionRangeType GetOptionRange(OptionRangeType min, OptionRangeType max);

/**
 * Gets a valid int option value from @ref cin in the range @p min and @p max,
 * inclusive.
 */
int GetOptionRange(int min, int max);

/**
 * Parses the next word from @ref cin, returning a string equal to either @p a
 * or @p b.
 */
std::string GetChoice(std::string a, std::string b);

/**
 * Gets the next int from @ref cin, returning an int equal to either @p a or @p
 * b.
 */
int GetChoice(int a, int b);

/**
 * Returns true if the next word in @ref cin matches @p trueString; otherwise,
 * returns false.
 */
bool GetBoolChoice(std::string trueString, std::string falseString);

namespace solitaire {
  const int kOneCardGame = 1;
  const int kThreeCardGame = 3;

  /**
   * Display the welcome message and prompt user for type of game (one-card or
   * three-card). Returns the number of cards to use in the game.
   */
  int GetGameConfig();

  enum class Play { TALON = 1, MOVE, HINT, RESTART };

  enum class Move { TALON_TO_FOUNDATION = 1, TABLEAU_TO_FOUNDATION,
      TALON_TO_TABLEAU, TABLEAU_TO_TABLEAU, FOUNDATION_TO_TABLEAU };

  /**
   * Display playing options and prompt user to enter choice. Returns the play
   * if valid.
   */
  Play GetPlay();

  /**
   * Does the selected play option.
   */
  bool DoPlay(Board& game, Play playOption);

  /**
   * Does the selected move option.
   */
  bool DoMove(Board& game, Move moveOption);
}
