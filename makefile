.PHONY= clean test

CC=g++
OPTIONS= -g -std=c++11 -lncurses
LIBDIR=lib
SRCDIR=src
TESTDIR=test
_OBJ=deck.o
OBJ=$(patsubst %,$(SRCDIR)/%,$(_OBJ))
_TESTOBJ=deckTests.o
TESTOBJ=$(patsubst %,$(TESTDIR)/%,$(_TESTOBJ))

all: $(SRCDIR)/main.cpp $(OBJ)
	$(CC) $(OPTIONS) -I$(LIBDIR) $< $(OBJ) -o mtgCalc.exec

test: $(TESTDIR)/test.cpp $(OBJ) $(TESTOBJ)
	$(CC) $(OPTIONS) -I$(LIBDIR) $< $(OBJ) $(TESTOBJ) -o test.exec
	./test.exec

$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	$(CC) $(OPTIONS) -c -I$(LIBDIR) -o $@ $<

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(OPTIONS) -c -I$(LIBDIR) -o $@ $<

clean:
	rm -f $(OBJ) $(TESTOBJ)
	rm -f *.exec
