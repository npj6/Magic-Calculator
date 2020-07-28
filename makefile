.PHONY= clean test

CC=g++
OPTIONS= -g -std=c++11
LIBDIR=lib
SRCDIR=src
TESTDIR=test
_OBJ=deckManager.o
OBJ=$(patsubst %,$(SRCDIR)/%,$(_OBJ))
_TESTOBJ=deckManagerTests.o
TESTOBJ=$(patsubst %,$(TESTDIR)/%,$(_TESTOBJ))

all: $(SRCDIR)/main.cpp $(OBJ)
	$(CC) $(OPTIONS) -I$(LIBDIR) $< $(OBJ) -o mtgCalc.exec

test: $(TESTDIR)/test.cpp $(LIBDIR)/catch2/catch.hpp $(OBJ) $(TESTOBJ)
	$(CC) $(OPTIONS) -I$(LIBDIR) $< $(OBJ) $(TESTOBJ) -o test.exec
	./test.exec

$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	$(CC) $(OPTIONS) -c -I$(LIBDIR) -o $@ $<

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(OPTIONS) -c -I$(LIBDIR) -o $@ $<

$(LIBDIR)/catch2/catch.hpp:
	wget -O $@ https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp

clean:
	rm -f $(OBJ)
	rm *.exec
