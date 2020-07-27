#include "deckManager.h"
#include <iostream>

int main (void) {
  MTGCALC::DeckManager dm;
  dm.addCard("NOMBRE", 23);
  std::cout << dm.deckList() << std::endl;
  return 0;
}
