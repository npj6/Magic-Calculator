#include "catch2/catch.hpp"
#include "deck.h"

//A card exists
bool cardExists(const MTGCALC::Deck &deck, const std::string &cardName, unsigned cardCopies) {
  for(int i=0; i<deck.getCardCount(); i++) {
    MTGCALC::Card card = deck.getCard(i);
    if(card.name == cardName) {
      UNSCOPED_INFO("Card copies: " << card.copies);
      if(card.copies == cardCopies) {
        return true;
      }
    }
  }
  UNSCOPED_INFO("Card not found");
  return false;
}

//All cards exist
void cardsExist(const MTGCALC::Deck &deck, const std::vector<std::string> &cardNames, const std::vector<unsigned> &cardCopies) {
  for(int i=0; i<cardNames.size() && i<cardCopies.size(); i++) {
    INFO(cardNames[i] << ": " << cardCopies[i] << " copies required.");
    REQUIRE(cardExists(deck, cardNames[i], cardCopies[i]));
  }
}

TEST_CASE("Deck is modified") {
  MTGCALC::Deck deck;
  REQUIRE(deck.getCardCount() == 0);

  //Initial state: Adds 2xCard 1 & 3xCard 2
  std::string name0 = "Card 1";
  unsigned copies0 = 2;
  std::string name1 = "Card 2";
  unsigned copies1 = 3;

  deck.addCard(name0, copies0);
  REQUIRE(deck.getCardCount() == 1);
  REQUIRE(cardExists(deck, name0, copies0));

  deck.addCard(name1, copies1);
  REQUIRE(deck.getCardCount() == 2);
  REQUIRE(cardExists(deck, name0, copies0));
  REQUIRE(cardExists(deck, name1, copies1));

  SECTION("Cards are added") {
    //Adds 2xCard 1
    unsigned add0 = 2;
    deck.addCard(name0, add0);
    REQUIRE(deck.getCardCount() == 2);
    REQUIRE(cardExists(deck, name0, copies0+add0));
    REQUIRE(!cardExists(deck, name0, copies0));
    REQUIRE(cardExists(deck, name1, copies1));
  }

  SECTION("Cards are deleted") {
    //Deletes Card 2
    deck.deleteCard(1);
    REQUIRE(deck.getCardCount() == 1);
    REQUIRE(cardExists(deck, name0, copies0));
    REQUIRE(!cardExists(deck, name1, copies1));

    //Adds 3xCard 2
    deck.addCard(name1, copies1);
    REQUIRE(deck.getCardCount() == 2);
    REQUIRE(cardExists(deck, name0, copies0));
    REQUIRE(cardExists(deck, name1, copies1));

    //Deletes Card 1
    deck.deleteCard(0);
    REQUIRE(deck.getCardCount() == 1);
    REQUIRE(!cardExists(deck, name0, copies0));
    REQUIRE(cardExists(deck, name1, copies1));

    //Deletes Card 2
    deck.deleteCard(0);
    REQUIRE(deck.getCardCount() == 0);
    REQUIRE(!cardExists(deck, name0, copies0));
    REQUIRE(!cardExists(deck, name1, copies1));
  }

  SECTION("Cards are modified") {
    unsigned newCopies0 = 5;
    std::string newName0 = "Birds of Paradise";
    unsigned newCopies1 = 1;
    std::string newName1 = "Forest";

    //Changes Card 1 from 2 to 5
    deck.modifyCard(0, newCopies0);
    REQUIRE(deck.getCardCount() == 2);
    REQUIRE(cardExists(deck, name0, newCopies0));
    REQUIRE(!cardExists(deck, name0, copies0));
    REQUIRE(cardExists(deck, name1, copies1));

    //Changes Card 1 to Birds of Paradise
    deck.modifyCard(0, newName0);
    REQUIRE(deck.getCardCount() == 2);
    REQUIRE(cardExists(deck, newName0, newCopies0));
    REQUIRE(!cardExists(deck, name0, newCopies0));
    REQUIRE(cardExists(deck, name1, copies1));

    //Changes Card 2 to Forest
    deck.modifyCard(1, newName1);
    REQUIRE(deck.getCardCount() == 2);
    REQUIRE(cardExists(deck, newName0, newCopies0));
    REQUIRE(cardExists(deck, newName1, copies1));
    REQUIRE(!cardExists(deck, name1, copies1));

    //Changes Forest from 3 to 1
    deck.modifyCard(1, newCopies1);
    REQUIRE(deck.getCardCount() == 2);
    REQUIRE(cardExists(deck, newName0, newCopies0));
    REQUIRE(cardExists(deck, newName1, newCopies1));
    REQUIRE(!cardExists(deck, newName1, copies1));
  }
}

TEST_CASE("Deck is read from file") {
  SECTION("aetherhub") {
    std::ifstream file("test/decks/aetherhub.txt");
    REQUIRE(file.is_open());
    MTGCALC::Deck deck(file);
    std::vector<std::string> names = {
      "Swamp",
      "Kroxa, Titan of Death's Hunger",
      "Temple of Malice",
      "Blood Crypt",
      "Fabled Passage",
      "Tymaret Calls the Dead",
      "Mire Triton",
      "Village Rites",
      "Castle Locthwain",
      "Mountain",
      "Liliana, Waker of the Dead",
      "Witch's Oven",
      "Cauldron Familiar",
      "Claim the Firstborn",
      "Priest of Forgotten Gods",
      "Woe Strider",
      "Chandra, Acolyte of Flame",
    };
    std::vector<unsigned> copies = {
      6, 4, 3, 4, 3, 3, 4, 3, 2, 6, 2, 4, 4, 3, 4, 3, 2
    };
    cardsExist(deck, names, copies);
    file.close();
  }

  SECTION("cockatrice") {
    std::ifstream file("test/decks/cockatrice.txt");
    REQUIRE(file.is_open());
    MTGCALC::Deck deck(file);
    std::vector<std::string> names = {};
    std::vector<unsigned> copies = {};
    cardsExist(deck, names, copies);
    file.close();
  }

  SECTION("deckbox") {
    std::ifstream file("test/decks/deckbox.txt");
    REQUIRE(file.is_open());
    MTGCALC::Deck deck(file);
    std::vector<std::string> names = {
      "Ancient Tomb",
      "Bountiful Promenade",
      "Breeding Pool",
      "Cavern of Souls",
      "Command Tower",
      "Exotic Orchard",
      "Forest",
      "Irrigated Farmland",
      "Island",
      "Krosan Verge",
      "Morphic Pool",
      "Mountain",
      "Murmuring Bosk",
      "Myriad Landscape",
      "Overgrown Tomb",
      "Path of Ancestry",
      "Plains",
      "Reflecting Pool",
      "Sea of Clouds",
      "Sheltered Thicket",
      "Swamp",
      "Temple of the False God",
      "Unclaimed Territory",
      "Urborg, Tomb of Yawgmoth",
      "Watery Grave",
      "Anguished Unmaking",
      "Artificial Evolution",
      "Austere Command",
      "Cairn Wanderer",
      "Call to the Kindred",
      "Chameleon Colossus",
      "Chromatic Lantern",
      "Chromium, the Mutable",
      "Coat of Arms",
      "Congregation at Dawn",
      "Cultivate",
      "Cyclonic Rift",
      "Deadeye Navigator",
      "Demonic Tutor",
      "Demonlord Belzenlok",
      "Door of Destinies",
      "Dragon Tempest",
      "Dragon's Hoard",
      "Dragonlord Atarka",
      "Dragonlord Dromoka",
      "Dragonlord Kolaghan",
      "Dragonlord Ojutai",
      "Dragonlord Silumgar",
      "Eladamri's Call",
      "Etali, Primal Storm",
      "Faeburrow Elder",
      "Forerunner of the Empire",
      "Ghalta, Primal Hunger",
      "Graveshifter",
      "Helm of the Host",
      "Herald's Horn",
      "Kindred Discovery",
      "Kindred Dominance",
      "Kodama's Reach",
      "Kroxa, Titan of Death's Hunger",
      "Morophon, the Boundless",
      "Nezahal, Primal Tide",
      "Nicol Bolas",
      "Nicol Bolas, the Ravager",
      "Odric, Lunarch Marshal",
      "Palladia-Mors, the Ruiner",
      "Phyrexian Arena",
      "Primevals' Glorious Rebirth",
      "Return of the Wildspeaker",
      "Rhystic Study",
      "Sakura-Tribe Elder",
      "Sarkhan Unbroken",
      "Smothering Tithe",
      "Sol Ring",
      "Sphinx's Revelation",
      "Sylvan Library",
      "Tetzimoc, Primal Death",
      "Thran Dynamo",
      "Toxic Deluge",
      "Uro, Titan of Nature's Wrath",
      "Urza's Incubator",
      "Urza's Ruinous Blast",
      "Vaevictis Asmadi, the Dire",
      "Vampiric Tutor",
      "Vanquisher's Banner",
      "Worn Powerstone",
      "Yavimaya Elder",
      "Zacama, Primal Calamity",
      "Zendikar Resurgent",
      "Zetalpa, Primal Dawn",
    };
    std::vector<unsigned> copies = {
      1, 1, 1, 1, 1, 1, 5, 1, 3, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };
    cardsExist(deck, names, copies);
    file.close();
  }

  SECTION("mtgGoldfish") {
    std::ifstream file("test/decks/mtgGoldfish.txt");
    REQUIRE(file.is_open());
    MTGCALC::Deck deck(file);
    std::vector<std::string> names = {
      "Aether Gust",
      "Blast Zone",
      "Brazen Borrower",
      "Breeding Pool",
      "Castle Vantress",
      "Expansion/Explosion",
      "Fabled Passage",
      "Forest",
      "Growth Spiral",
      "Island",
      "Ketria Triome",
      "Mountain",
      "Mystical Dispute",
      "Negate",
      "Nightpack Ambusher",
      "Opt",
      "Shark Typhoon",
      "Steam Vents",
      "Stomping Ground",
      "Uro, Titan of Nature's Wrath",
      "Wilderness Reclamation"
    };
    std::vector<unsigned> copies = {
      2, 2, 2, 4, 3, 4, 3, 2, 4, 2, 4, 1, 3, 2, 2, 3, 3, 4, 3, 3, 4
    };
    cardsExist(deck, names, copies);
    file.close();
  }

  SECTION("tappedOut") {
    std::ifstream file("test/decks/tappedOut.txt");
    REQUIRE(file.is_open());
    MTGCALC::Deck deck(file);
    std::vector<std::string> names = {
      "Anguished Unmaking (SOI) 242",
      "Arcane Sanctum (MYS1) 232",
      "Artificial Evolution (ONS)",
      "Arvad the Cursed (DAR) 191",
      "Blood Crypt (RNA) 245",
      "Breeding Pool (RNA) 246",
      "Bring to Light (BFZ) 209",
      "Cairn Wanderer (C20) 130",
      "Cascading Cataracts (AKH) 240",
      "Chameleon Colossus (C15) 178",
      "Charmbreaker Devils (JMP) 303",
      "Chromatic Lantern (GRN) 233",
      "Chromium, the Mutable (M19) 214",
      "Circuitous Route (GRN) 125",
      "Coat of Arms (MYS1) 58",
      "Command Tower (C20) 264",
      "Conflux (CON) 202",
      "Cultivate (M21) 177",
      "Cyclonic Rift (MM3) 35",
      "Demonic Tutor (MYS1) 93",
      "Demonlord Belzenlok (DAR) 86",
      "Dragonlord Atarka (DTK) 216",
      "Dragonlord Dromoka (DTK) 217",
      "Dragonlord Kolaghan (DTK) 218",
      "Dragonlord Ojutai (MYS1) 219",
      "Dragonlord Silumgar (DTK) 220",
      "Enlightened Tutor (EMA) 9",
      "Etali, Primal Storm (JMP) 314",
      "Exotic Orchard (C20) 273",
      "Explosive Vegetation (MYS1) 144",
      "Farseek (MYS1) 165",
      "Fellwar Stone (C17) 210",
      "Fist of Suns (C17) 211",
      "Forerunner of the Empire (RIX) 102",
      "Forest (JMP) 70",
      "Frontier Bivouac (C20) 275",
      "Ghalta, Primal Hunger (JMP) 399",
      "Godless Shrine (RNA) 248",
      "Grand Coliseum (C16) 299",
      "Hallowed Fountain (RNA) 251",
      "Herald's Horn (JMP) 469",
      "Heroes' Podium (BNG) 159",
      "In Garruk's Wake (C19) 121",
      "Island (JMP) 46",
      "Jodah, Archmage Eternal (DAR) 198",
      "Jungle Shrine (MYS1) 255",
      "Kodama's Reach (C20) 180",
      "Krosan Verge (C20) 285",
      "Merciless Eviction (C17) 179",
      "Mirari's Wake (C17) 181",
      "Mirrodin's Core (JMP) 492",
      "Mountain (JMP) 62",
      "Muldrotha, the Gravetide (DAR) 199",
      "Murmuring Bosk (C16) 308",
      "Mystic Confluence (BBD) 122",
      "Mystical Tutor (EMA) 62",
      "Nezahal, Primal Tide (RIX) 45",
      "Nicol Bolas (ME3) 163",
      "Nicol Bolas, the Ravager (M19) 218",
      "Opulent Palace (C20) 295",
      "Overgrown Tomb (GRN) 253",
      "Painful Truths (C20) 134",
      "Palladia-Mors, the Ruiner (M19) 219",
      "Path of Ancestry (C20) 298",
      "Phyrexian Arena (MYS1) 144",
      "Plains (JMP) 38",
      "Primevals' Glorious Rebirth (DAR) 201",
      "Reflecting Pool (CNS) 210",
      "Sacred Foundry (GRN) 254",
      "Sakura-Tribe Elder (C20) 187",
      "Sarkhan Unbroken (WARMED) 8",
      "Savage Lands (C18) 275",
      "Seaside Citadel (C18) 277",
      "Shard Convergence (CON)",
      "Skyshroud Claim (BBD) 213",
      "Sphinx's Revelation (MM3) 187",
      "Steam Vents (GRN) 257",
      "Stomping Ground (RNA) 259",
      "Supreme Verdict (MYS1) 201",
      "Swamp (JMP) 54",
      "Sylvan Library (EMA) 187",
      "Temple Garden (GRN) 258",
      "Tempt with Discovery (MYS1) 183",
      "Tetzimoc, Primal Death (RIX) 86",
      "Vaevictis Asmadi, the Dire (M19) 225",
      "Vampiric Tutor (EMA) 112",
      "Vandalblast (C15) 170",
      "Vanquisher's Banner (XLN) 251",
      "Vivid Grove (C17) 291",
      "Watery Grave (GRN) 259",
      "Yavimaya Elder (MYS1) 166",
      "Zacama, Primal Calamity (RIX) 174",
      "Zendikar Resurgent (C17) 160",
      "Zetalpa, Primal Dawn (C20) 107"
    };
    std::vector<unsigned> copies = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1,
      1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };
    cardsExist(deck, names, copies);
    file.close();
  }
}
