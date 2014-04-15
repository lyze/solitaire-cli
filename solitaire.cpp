/**
 * @file solitaire.cpp
 * @author David Xu
 * @author Connie Yuan
 * @brief Implements solitaire (Klondike).
 */
#include <cstring>
#include <limits>
#include "solitaire.h"

using namespace std;
using namespace solitaire;

int SetupGame() {
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

bool PerformPlay(Play play, Board board) {
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
    // todo: hint
    return true;
  case Play::RESTART:
    // todo: restart
    return true;
  default:
    return false;
  }
}

int IntOf(Play play) {
  return static_cast<int>(play);
}

static inline bool IsPlayOptionValid(int option) {
  return option >= IntOf(Play::DEAL) && option <= IntOf(Play::RESTART);
}

Play GetPlay () {
  int option = 0;
  cout << "Play Options:" << endl
       << "(1) Deal new upturned card(s)" << endl
       << "(2) Move card(s)" << endl
       << "(3) Get a hint" << endl
       << "(4) Restart the game" << endl << endl
       << "Select a move: ";
  cin >> option;

  while (!IsPlayOptionValid(option)) {
    cout << "Please enter a valid play option: ";
    cin >> option;
  }
  // todo: error checking for getPlay

  // TODO: GetPlay
  // Move card
  // - Which stack would you like to move?
  // - How many cards?
  // - To where would you like to move the card(s)?

  if (option == IntOf(Play::DEAL)) {
    return Play::DEAL;
  } else if (option == IntOf(Play::MOVE)) {
    return Play::MOVE;
  } else if (option == IntOf(Play::HINT)) {
    return Play::HINT;
  }
  return Play::RESTART;
}

int main (int argc, char* argv[]) {
  int numOpenCards;

  // start the game and display board
  numOpenCards = SetupGame();
  Board game(numOpenCards);
  cout << endl;

  // while the game still has valid moves or the user wants to continue playing
  while (game) {
    game.DrawBoard();
    while (!PerformPlay(GetPlay(), game)) { }
  }

  Board::Status status = game.GetStatus();
  // TODO: Edge case: Check if initial game was stuck
  if (status == Board::Status::WON) {
    //display winning message
  } else if (status == Board::Status::STUCK) {
    //display losing message
  }

  return 0;
}
