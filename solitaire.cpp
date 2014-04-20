/**
 * @file solitaire.cpp
 * @author David Xu
 * @author Connie Yuan
 * @brief Implements solitaire (Klondike).
 */
#include <cassert>
#include <limits>
#include "solitaire.h"

using namespace std;

int GetInt() {
  int n;
  while (true) {
    if (cin >> n) {
      break;
    } else {
      cin.clear();
      cin.ignore();
    }
  }
  return n;
}

int GetIntOption(int min, int max) {
  int option = GetInt();
  while (option < min || option > max) {
    cout << "Please enter a valid option between "
         << min  << " and " << max << ": ";
    option = GetInt();
  }
  return option;
}

template <typename OptionRangeType>
OptionRangeType GetOption(OptionRangeType min, OptionRangeType max) {
  return static_cast<OptionRangeType>(GetIntOption(static_cast<int>(min),
                                                   static_cast<int>(max)));
}

string GetChoice(string a, string b) {
  string option = GetString();
  while (!(a == option || b == option)) {
    cout << "Please enter either " << a << " or " << b << ": ";
    option = GetString();
  }
  return option;
}

bool GetBoolChoice(string trueString, string falseString) {
  return trueString == GetChoice(trueString, falseString);
}

int GetChoice(int a, int b) {
  int option = GetInt();
  while (!(option == a || option == b)) {
    cout << "Please enter either " << a << " or " << b << ": ";
    option = GetInt();
  }
  return option;
}

string GetString() {
  string s;
  cin >> s;
  return s;
}

namespace solitaire {
  int SetupGame() {
    cout << "Welcome to Solitaire!" << endl
         << "Please enter the size of the talon (" << kOneCardGame << " or "
         << kThreeCardGame << "): ";
    int option = GetInt();
    while (option != kOneCardGame && option != kThreeCardGame) {
      cout << "Please enter either " << kOneCardGame << " or " << kThreeCardGame
           << ": ";
      option = GetInt();
    }
    return option;
  }

  Play GetPlay() {
    cout << "Play Options:" << endl
         << "(1) Deal new upturned card(s)" << endl
         << "(2) Move card(s)" << endl
         << "(3) Get a hint" << endl
         << "(4) Restart the game" << endl
         << endl
         << "Select an option: ";
    int option = GetIntOption(static_cast<int>(Play::TALON),
                              static_cast<int>(Play::RESTART));

    return static_cast<Play>(option);
  }

  bool DoMove(Board& game, Move moveOption) {
    switch(moveOption) {
    case Move::TALON_TO_FOUNDATION:
      return game.DoMoveTalonToFoundation();
    case Move::TABLEAU_TO_FOUNDATION:
      cout << "Which tableau pile contains the card to move to the foundation? ";
      return game.DoMoveTableauToFoundation(GetOption(0, kTableauSize - 1));
    case Move::TALON_TO_TABLEAU:
      cout << "To which tableau pile will the talon card move? ";
      return game.DoMoveTalonToTableau(GetOption(0, kTableauSize - 1));
    case Move::TABLEAU_TO_TABLEAU: {
      cout << "From which tableau pile will the card(s) move? ";
      int fromIdx = GetOption(0, kTableauSize - 1);
      cout << "To which tableau pile will the card(s) move? ";
      int toIdx = GetOption(0, kTableauSize - 1);
      return game.DoMoveTableauToTableau(fromIdx, toIdx);
    }
    case Move::FOUNDATION_TO_TABLEAU: {
      cout << "From which foundation pile will the card move? ";
      int foundationIdx = GetOption(0, kNumSuits - 1);
      cout << "To which tableau pile will the card move? ";
      int tableauIdx = GetOption(0, kTableauSize - 1);
      return game.DoMoveFoundationToTableau(foundationIdx, tableauIdx);
    }
    default:
      assert(false);
    }
  }

  bool DoPlay(Board& game, Play playOption) {
    switch (playOption) {
    case Play::TALON:
      return game.DoNewTalon();
    case Play::MOVE:
      cout << endl
           << "Move options:" << endl
           << "(1) Talon card to the foundation" << endl
           << "(2) Tableau card to the foundation" << endl
           << "(3) Talon card to the tableau" << endl
           << "(4) Tableau to the tableau" << endl
           << "(5) Foundation to the tableau" << endl
           << endl
           << "Select a move: ";
      return DoMove(game, GetOption(Move::TALON_TO_FOUNDATION,
                                    Move::FOUNDATION_TO_TABLEAU));
    case Play::HINT:
      game.DoGetHint();
      return true;
    case Play::RESTART:
      cout << "Are you sure you want to reset the board and restart your game (y/n)? ";
      if (GetBoolChoice("y", "n")) {
        game.Reset();
      }
      return true;
    default:
      assert(false);
    }
  }
}

using namespace solitaire;

int main(int argc, char* argv[]) {
  int numOpenCards;

  // start the game and display board
  numOpenCards = SetupGame();
  Board game(numOpenCards);

  // while the game still has valid moves or the user wants to continue playing
  while (game) {
    cout << endl;
    game.DrawBoard();
    if (!DoPlay(game, GetPlay())) {
      cout << endl
           << "Nothing done." << endl;
    }
    Board::Status status = game.GetStatus();
    if (status == Board::Status::WON) {
      cout << endl
           << "You won!" << endl;
    } else if (status == Board::Status::STUCK) {
      cout << "You have no more valid moves! Would you like to restart (y/n)? " << endl;
      if (GetBoolChoice("y", "n")) {
        cout << "Resetting..." << endl;
        game.Reset(SetupGame());
      }
    }
  }

  return 0;
}
