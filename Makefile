#Compiler Command
CC=g++

#Compiler Flags
CFLAGS=-c -Wall

LINKERS=rt

###################################################################

all: gskConsensus

gskConsensus: Logic.o Logger.o Main.o
	$(CC) -l$(LINKERS) Logic.o Logger.o Main.o -o gskConsensus

Logic.o: Logic.cpp
	$(CC) $(CFLAGS) Logic.cpp

Logger.o: Logger.cpp
	$(CC) $(CFLAGS) Logger.cpp

Main.o: Main.cpp Linux.h Logger.h
	$(CC) $(CFLAGS) Main.cpp

clean:
	rm *.o gskConsensus
