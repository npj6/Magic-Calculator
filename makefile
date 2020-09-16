.PHONY= clean test

CC=g++
OPTIONS= -g -std=c++11
LIBDIR=lib
SRCDIR=src
TESTDIR=test
OBJDIR=obj
TESTOBJDIR=$(OBJDIR)/test
_OBJ=deck.o
OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))
_TESTOBJ=deckTests.o
TESTOBJ=$(patsubst %,$(TESTOBJDIR)/%,$(_TESTOBJ))

all: $(SRCDIR)/main.cpp $(OBJ)
	$(CC) $(OPTIONS) -I$(LIBDIR) $< $(OBJ) -o mtgCalc

test: $(TESTDIR)/test.cpp $(OBJ) $(TESTOBJ)
	$(CC) $(OPTIONS) -I$(LIBDIR) $< $(OBJ) $(TESTOBJ) -o tests
	./tests

$(TESTOBJDIR)/%.o: $(TESTDIR)/%.cpp
	$(CC) $(OPTIONS) -c -I$(LIBDIR) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(OPTIONS) -c -I$(LIBDIR) -o $@ $<

clean:
	rm -f $(OBJ) $(TESTOBJ)
	rm -f mtgCalc tests
