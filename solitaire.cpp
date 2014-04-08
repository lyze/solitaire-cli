/**
 * @file solitaire.cpp
 * @author David Xu
 * @author Connie Yuan
 * @brief Implements solitare (Klondike).
 */
#include <cstring>
#include <limits>
#include "solitaire.h"

using namespace std;
using namespace solitaire;

/* Display the welcome message and prompt user for type
   of game (one-card or three-card)
 */
int SetupGame () {
  int numOpenCards = 0;

  // Display welcome and set up game
  cout << "Welcome to Solitaire!\n"
       << "Please enter " << ONE_CARD_GAME << " for a one-card game"
       << " or " << THREE_CARD_GAME << " for a three-card game: ";

  do {
    if (!(cin >> numOpenCards)) {
      cin.clear();
      cin.ignore();
      cout << "Please enter a valid card selection of " << ONE_CARD_GAME
           << " or " << THREE_CARD_GAME << ": ";
    }
  } while (numOpenCards != ONE_CARD_GAME && numOpenCards != THREE_CARD_GAME);

  return numOpenCards;
}

/* Perform the user selected play. If option is invalid, return
   false. If play performed, return true.
*/
bool PerformPlay (Play play, Board board) {
  switch (play) {
  case Play::DEAL:
    //todo: deal
    // board.DrawBoard();
    return true;
  case Play::MOVE:
    // todo: move
    // board.DrawBoard();
    return true;
  case Play::HINT:
    // todo:
    return true;
  case Play::RESTART:
    // todo: restart
    return true;
  default:
    return false;
  }
}

/* Display playing options and prompt user to enter choice
*/
Play GetPlay () {
  int play = 0;
  cout << "Play Options: \n"
       << "(1) Deal new upturned card(s) \n"
       << "(2) Move card(s) \n"
       << "(3) Get a hint \n"
       << "(4) Restart the game \n \n"
       << "Select a move: ";
  cin >> play;
  cout << "Please enter a valid play option: ";
  // todo: error checking for getPlay

  // TODO: GetPlay
  // Move card
  // - Which stack would you like to move?
  // - How many cards?
  // - To where would you like to move the card(s)?

   return Play::RESTART;
}

int main (int argc, char* argv[]) {
  int numOpenCards;

  // start the game and display board
  numOpenCards = SetupGame();
  Board game(numOpenCards);
  cout << endl;

  while (game) {
    game.DrawBoard();
    while (!PerformPlay(GetPlay(), game)) {
  }

  }
  Board::Status status = game.GetStatus();
  // TODO: Edge case: Check if initial game was stuck
  if (status == Board::Status::WON) {
    //display winning message
  } else if (status == Board::Status::STUCK) {
    //display losing message
  }

  // play the game



  return 0;
}
