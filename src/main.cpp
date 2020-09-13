#include "deck.h"
#include <iostream>
#include <fstream>

int main (void) {
  //All complex input is recieved through a text file
  // ./mtgCalc -h -> user help
  // ./mtgCalc file -> loads the deck, shows the deck, asks for a single Situation expresion and calculates its probability
  // ./mtgCalc file -e file -> loads the deck and the expresions files, calculates the probability of each Situation expresion
  std::ifstream file("test/decks/aetherhub.txt");
  if (file.is_open()) {
    MTGCALC::Deck dm(file);
    std::cout << dm.deckList() << std::endl;
  } else {
    std::cout << "bad file" << std::endl;
  }
  file.close();
  return 0;
}
