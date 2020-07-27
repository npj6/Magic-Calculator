.PHONY= clean test

CC=g++
OPTIONS= -g -std=c++11
LIBDIR=lib
INCLUDEDIR=include
_OBJ=deckManager.o
OBJ=$(patsubst %,$(LIBDIR)/%,$(_OBJ))

all: main.cpp $(OBJ)
	$(CC) $(OPTIONS) -I$(INCLUDEDIR) main.cpp $(OBJ) -o mtgCalc.exec

test: $(INCLUDEDIR)/catch.hpp
	echo exec the test > test.exec

$(LIBDIR)/%.o: $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) -c -I$(INCLUDEDIR) -o $@ $<

$(INCLUDEDIR)/catch.hpp:
	wget -O $@ https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp

clean:
	rm -f $(OBJ)
	rm *.exec
