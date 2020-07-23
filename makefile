.PHONY= clean

CC=g++
OPTIONS= -g -std=gnu++0x
EXEC=mtgCalc.exec
LIBDIR=lib
INCLUDEDIR=include
_OBJ=deckManager.o
OBJ=$(patsubst %,$(LIBDIR)/%,$(_OBJ))

all: main.cpp $(OBJ)
	$(CC) $(OPTIONS) -I$(INCLUDEDIR) main.cpp $(OBJ) -o $(EXEC)

$(LIBDIR)/%.o: $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) -c -I$(INCLUDEDIR) -o $@ $<

clean:
	rm -f $(OBJ) $(EXEC)
