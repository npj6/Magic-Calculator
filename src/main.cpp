#include "deck.h"
#include <iostream>
#include <ncurses.h>

int main (void) {
  MTGCALC::Deck dm;
  dm.addCard("NOMBRE", 23);
  std::cout << dm.deckList() << std::endl;
  return 0;
}
