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
 * Display the welcome message and prompt user for type of game (one-card or
 * three-card). Returns the number of cards to use in the game.
 */
int SetupGame();

int IntOf(solitaire::Board::Play play);

/**
 * Display playing options and prompt user to enter choice. Returns the play if
 * valid.
 */
solitaire::Board::Play GetPlay();
