/**
 * @file solitaire.cpp
 * @author David Xu
 * @author Connie Yuan
 * @brief Implements solitare (Klondike).
 */
#include <cstring>
#include "card.h"
#include "solitaire.h"

using namespace std;
using namespace solitaire;

int main (int argc, char* argv[]) {
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
    
  if (numOpenCards == ONE_CARD_GAME) {
      // todo
  } else if (numOpenCards == THREE_CARD_GAME) {
      // todo
  }

  // Init board with numOpenCards

  // Draw playing field


  return 0;
}
