CC := g++
SRCDIR := src
INCDIR := include
BUILDDIR := build
TARGET := bin/fallout_hack
CCFLAGS := -std=c++11 -c

all: $(TARGET)

$(TARGET): hack.o game.o text.o words.o
	$(CC) $(BUILDDIR)/hack.o $(BUILDDIR)/game.o $(BUILDDIR)/text.o $(BUILDDIR)/words.o -lncursesw -o bin/fallout_hack

hack.o: $(SRCDIR)/fallout_hack.cpp $(INCDIR)/FalloutGame.h
	$(CC) $(CCFLAGS) -o $(BUILDDIR)/hack.o $(SRCDIR)/fallout_hack.cpp

game.o: $(SRCDIR)/FalloutGame.cpp $(INCDIR)/FalloutGame.h $(INCDIR)/FalloutText.h $(INCDIR)/FalloutWords.h
	$(CC) $(CCFLAGS) -o $(BUILDDIR)/game.o $(SRCDIR)/FalloutGame.cpp

text.o: $(SRCDIR)/FalloutText.cpp
	$(CC) $(CCFLAGS) -o $(BUILDDIR)/text.o $(SRCDIR)/FalloutText.cpp

words.o: $(SRCDIR)/FalloutWords.cpp
	$(CC) $(CCFLAGS) -o $(BUILDDIR)/words.o $(SRCDIR)/FalloutWords.cpp

clean:
	rm build/*.o bin/fallout_hack
