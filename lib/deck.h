#ifndef MTGCALC_DECK_H
  #define MTGCALC_DECK_H

  #include <vector>
  #include <string>
  #include <stdexcept>
  #include <fstream>

  namespace MTGCALC {

    typedef struct Card_T {
      std::string name;
      unsigned copies;
      Card_T (const std::string &n, unsigned c) { name = n; copies = c; }
    } Card;


    class Deck {
      private:
        std::vector<Card> cards;

        unsigned findCard(const std::string &name);
      public:
        Deck() {};

        Deck(std::ifstream &file);

        void addCard(const std::string &name, unsigned copies);

        void deleteCard(unsigned position);

        void modifyCard(unsigned position, unsigned newCopies);
        void modifyCard(unsigned position, const std::string &newName);

        //trusted while testing
        std::string deckList(void) const;
        unsigned getCardCount() const;
        Card getCard(unsigned position) const;
    };
  }

#endif
