CC = g++
INCLUDE_DIR := include
SRC := src
LIBS=-lsfml-graphics -lsfml-window -lsfml-system 

all: objdir obj/Node.o obj/Edge.o obj/Graph.o obj/main.o
	$(CC) -o graph-app obj/Node.o obj/Edge.o obj/Graph.o obj/main.o $(LIBS)
	rm -r obj
objdir:
	mkdir -p obj
obj/Node.o: $(SRC)/Node.cc
	$(CC) -o obj/Node.o -I$(INCLUDE_DIR) -c $(SRC)/Node.cc $(LIBS)
obj/Edge.o: $(SRC)/Edge.cc
	$(CC) -o obj/Edge.o -I$(INCLUDE_DIR) -c $(SRC)/Edge.cc $(LIBS)
obj/Graph.o: $(SRC)/Graph.cc
	$(CC) -o obj/Graph.o -I$(INCLUDE_DIR) -c $(SRC)/Graph.cc $(LIBS)
obj/main.o: main.cc
	$(CC) -o obj/main.o -I$(INCLUDE_DIR) -c main.cc $(LIBS)
clean:
	rm -r obj
