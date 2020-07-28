#ifndef MTGCALC_DECKMANAGER_H
  #define MTGCALC_DECKMANAGER_H

  #include <vector>
  #include <string>
  #include<stdexcept>

  namespace MTGCALC {

    typedef struct Card_T {
      std::string name;
      unsigned copies;
      Card_T (const std::string &n, unsigned c) { name = n; copies = c; }
    } Card;

    class DeckManager {
      private:
        std::vector<Card> cards;

        unsigned findCard(const std::string &name);
      public:
        DeckManager() {};

        void addCard(const std::string &name, unsigned copies);

        void deleteCard(unsigned position);

        Card getCard(unsigned position);

        void modifyCard(unsigned position, unsigned newCopies);
        void modifyCard(unsigned position, const std::string newName);

        std::string deckList(void);
    };
  }

#endif
