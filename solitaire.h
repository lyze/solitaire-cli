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
 * PLAYING if moves left.
 */
// TODO: enum Play
enum class Play { DEAL = 1, MOVE = 2, HINT = 3, RESTART = 4 };

int SetupGame();
// TODO: Move and implement PerformPlay in Board class
bool PerformPlay(int play, solitaire::Board board);
Play GetPlay();
