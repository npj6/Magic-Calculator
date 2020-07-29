#include "catch2/catch.hpp"
#include "deck.h"

TEST_CASE("Decklist is modified") {
  MTGCALC::Deck dm;
  REQUIRE(dm.deckList() == "");

  dm.addCard("Card 1", 2);
  REQUIRE(dm.deckList() == "#0 2 Card 1\n");

  dm.addCard("Card 2", 3);
  REQUIRE(dm.deckList() == "#0 2 Card 1\n#1 3 Card 2\n");

  dm.addCard("Card 1", 2);
  REQUIRE(dm.deckList() == "#0 4 Card 1\n#1 3 Card 2\n");

  SECTION("Cards are deleted") {
    dm.deleteCard(1);
    REQUIRE(dm.deckList() == "#0 4 Card 1\n");

    dm.addCard("Card 2", 3);
    REQUIRE(dm.deckList() == "#0 4 Card 1\n#1 3 Card 2\n");

    dm.deleteCard(0);
    REQUIRE(dm.deckList() == "#0 3 Card 2\n");

    dm.deleteCard(0);
    REQUIRE(dm.deckList() == "");
  }

  SECTION("Cards are modified") {
    dm.modifyCard(0, 2);
    REQUIRE(dm.getCard(0).copies == 2);

    dm.modifyCard(0, "Birds of Paradise");
    REQUIRE(dm.getCard(0).name == "Birds of Paradise");

    dm.modifyCard(1, 2);
    REQUIRE(dm.getCard(1).copies == 2);

    dm.modifyCard(1, "Forest");
    REQUIRE(dm.getCard(1).name == "Forest");

    REQUIRE(dm.deckList() == "#0 2 Birds of Paradise\n#1 2 Forest\n");
  }
}
