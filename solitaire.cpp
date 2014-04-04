/**
 * @file solitaire.cpp
 * @author David Xu
 * @author Connie Yuan
 * @brief Implements solitare (Klondike).
 */
#include <cstring>
#include "solitaire.h"

using namespace std;
using namespace solitaire;

/* Display the welcome message and prompt user for type
   of game (one-card or three-card)
 */
int SetupGame () {
  int numOpenCards;
  
  // Display welcome and set up game
  cout << "Welcome to Solitaire!\n"
       << "Please enter " << ONE_CARD_GAME << " for a one-card game" 
       << " or " << THREE_CARD_GAME << " for a three-card game: ";
  cin >> numOpenCards;
  
  while (numOpenCards != ONE_CARD_GAME && numOpenCards != THREE_CARD_GAME) {
    cout << "Please enter a valid card selection of " << ONE_CARD_GAME 
	 << " or " << THREE_CARD_GAME << ": ";
    cin >> numOpenCards;
  }
  
  return numOpenCards;
}

/* Perform the user selected play. If option is invalid, return
   false. If play performed, return true.
*/
bool PerformPlay (int play, Board board) {
  switch (play) {
  case DEAL:
    //todo: deal
    board.DrawBoard();
    return true;
  case MOVE:
    //move
    board.DrawBoard();
    return true;
  case HINT:
    //hint
    return true;
  case RESTART:
    //restart
    return true;
  default:
    return false;
  }
}

/* Display playing options and prompt user to enter choice 
*/
void GetPlay (Board board) {
  int play = 0;
  cout << "Play Options: \n"
       << "(1) Deal new upturned card(s) \n"
       << "(2) Move card(s) \n"
       << "(3) Get a hint \n"
       << "(4) Restart the game \n \n"
       << "Select a move: ";
  cin >> play;
  while (!PerformPlay(play, board)) {
    cout << "Please enter a valid play option: ";
    cin >> play;
  }
}

status GetGameStatus (Board board) {
  //todo
  return PLAYING;
}

int main (int argc, char* argv[]) {
  int numOpenCards;
  status gameStatus = PLAYING;

  // start the game and display board
  numOpenCards = SetupGame();
  Board board (numOpenCards);
  board.DrawBoard();

  // check moves at beginning to make sure game playable
  gameStatus = GetGameStatus(board);
  
  // play the game
  while (gameStatus == PLAYING) {
    GetPlay(board);
    gameStatus = GetGameStatus(board);
  }

  if (gameStatus == WON) {
    //display winning message
  } else if (gameStatus == LOST) {
    //display losing message
  }

  return 0;
}
