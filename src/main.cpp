#include "deck.h"
#include <iostream>
#include <fstream>
#include <string>

namespace MTGCALC {
  void showHelp(void) {std::cout << "HELP" << std::endl;}
}

int main (int argc, char *argv[]) {
  //All complex input is recieved through a text file
  // ./mtgCalc -h -> user help
  // ./mtgCalc file -> loads the deck, shows the deck, asks for a single Situation expresion and calculates its probability
  // ./mtgCalc file -e file -> loads the deck and the expresions files, calculates the probability of each Situation expresion
  // ./mtgCalc file -e file -s -> also shows the non calculable expressions in the file

  //Arguments handling

  std::string deckFileName;
  bool expressionsFileNext = false;
  std::string expressionsFileName;
  bool showIntermediateExpr = false;
  for(int i=1; i<argc; i++) {
    std::string arg = argv[i];
    if(arg == "-h") {
        MTGCALC::showHelp();
        return 0;
    } else if (arg == "-e") {
        expressionsFileNext = true;
    } else if (arg == "-s") {
        showIntermediateExpr = true;
    } else {
        if (expressionsFileNext && expressionsFileName.empty()) {
            expressionsFileName = arg;
            expressionsFileNext = false;
        } else if (deckFileName.empty()) {
            deckFileName = arg;
        }
    }
  }

  //Deck handling

  if (deckFileName.empty()) {
    std::cout << "No deck file specified." << std::endl << std::endl;
    MTGCALC::showHelp();
    return 0;
  }

  std::ifstream deckFile(deckFileName);
  if(!deckFile.is_open()) {
    std::cout << "Deck file could not be opened." << std::endl
      << "(Does the file exist?)" << std::endl;
    return 0;
  }

  MTGCALC::Deck deck(deckFile);
  deckFile.close();

  //Expression(s) handling and console input/output

  if (!expressionsFileName.empty()) {
    std::ifstream expressionsFile(expressionsFileName);
    if(!expressionsFile.is_open()) {
      std::cout << "Expressions file could not be opened." << std::endl
        << "(Does the file exist?)" << std::endl;
      return 0;
    }

    std::string line;
    while(std::getline(expressionsFile, line)) {
      if(line.back() == (char) 13) {
        line.pop_back();
      }
      //TODO: -s shows the non calculable expressions
      //send expression to interpreter, show results
    }
    expressionsFile.close();
  } else {
    std::cout << deck.deckList() << std::endl;
    std::cout << std::endl << "Enter the expression you want to calculate:" << std::endl;
    std::string expression;
    while (expression.empty()) {
      //TODO: non calculable expressions are saved and shown
      //TODO: asks if you want to save the expressions after finishing
      //TODO: multiple expressions, empty one to finish
      std::cin >> expression;
      //send expression to interpreter, show results
      if (false/*if expression is not ok*/) {
        expression = "";
        std::cout << "The expression is not correct. Please try again:" << std::endl;
      }
    }
  }
  return 0;
}
