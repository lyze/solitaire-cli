/**
 * @file solitaire.h
 * @author David Xu
 * @author Connie Yuan
 * @brief Prototypes of functions relevant to the card game Solitaire.
 */
#pragma once
#include "board.h"

const int ONE_CARD_GAME   = 1;
const int THREE_CARD_GAME = 3;

/**
 * WON if no moves left and player won, LOST if no moves left and player lost,
 * PLAYING if moves left, RESTART if user chooses to restart the game.
 */
// TODO: enum Play
enum class Play { DEAL = 1, MOVE, HINT, RESTART };

/**
 * Display the welcome message and prompt user for type of game (one-card or
 * three-card). Returns the number of cards to use in the game.
 */
int SetupGame();

// TODO: Move and implement PerformPlay in Board class
/**
 * Perform the user selected play. If option is invalid, return false. If play
 * performed, return true.
 */
bool PerformPlay(int play, solitaire::Board board);
int IntOf(Play play);

/**
 * Display playing options and prompt user to enter choice. Returns the play if
 * valid.
 */
Play GetPlay();
