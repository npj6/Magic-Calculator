#include "deck.h"

unsigned MTGCALC::Deck::findCard(const std::string &name) {
  for(unsigned i=0; i<cards.size(); i++) {
    if(cards[i].name == name) {
      return i;
    }
  }
  throw std::runtime_error("no card named "+name);
}

void MTGCALC::Deck::addCard(const std::string &name, unsigned copies) {
  try {
    cards[findCard(name)].copies += copies;
  } catch (const std::runtime_error &e) {
    cards.push_back(Card(name, copies));
  }
}

void MTGCALC::Deck::deleteCard(unsigned position) {
  if(position < cards.size()) { cards.erase(cards.begin() + position); }
}

MTGCALC::Card MTGCALC::Deck::getCard(unsigned position) {
  if(position < cards.size()) { return cards[position]; }
}

void MTGCALC::Deck::modifyCard(unsigned position, unsigned newCopies) {
  if(position < cards.size()) { cards[position].copies = newCopies; }
}
void MTGCALC::Deck::modifyCard(unsigned position, const std::string newName) {
  if(position < cards.size()) { cards[position].name = newName; }
}

std::string MTGCALC::Deck::deckList(void) {
  std::string output;
  for(unsigned i=0; i<cards.size(); i++) {
    output.push_back('#');
    output += std::to_string(i);
    output.push_back(' ');
    output += std::to_string(cards[i].copies);
    output.push_back(' ');
    output += cards[i].name;
    output.push_back('\n');
  }
  return output;
}
