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

/* WON if no moves left and player won,
   LOST if no moves left and player lost,
   PLAYING if moves left
 */
enum status {WON, LOST, PLAYING};
enum play   {DEAL = 1, MOVE = 2, HINT = 3, RESTART = 4};

int    SetupGame();
bool   PerformPlay(int play, solitaire::Board board);
void   GetPlay(solitaire::Board board);
status GetGameStatus(solitaire::Board board);
