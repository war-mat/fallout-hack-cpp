CC := g++
SRCDIR := src
INCDIR := include
BUILDDIR := build
BINDIR := bin
TARGET := $(BINDIR)/fallout_hack
CCFLAGS := -Wall -std=c++11 -c

all: $(TARGET)

$(TARGET): $(BUILDDIR)/hack.o $(BUILDDIR)/game.o $(BUILDDIR)/text.o $(BUILDDIR)/words.o $(BUILDDIR)/display.o $(BUILDDIR)/cursor.o
	$(CC) $(BUILDDIR)/hack.o $(BUILDDIR)/game.o $(BUILDDIR)/text.o $(BUILDDIR)/words.o $(BUILDDIR)/display.o $(BUILDDIR)/cursor.o -lncursesw -o $(TARGET)

$(BUILDDIR)/hack.o: $(SRCDIR)/fallout_hack.cpp $(INCDIR)/FalloutGame.h
	$(CC) $(CCFLAGS) -o $(BUILDDIR)/hack.o $(SRCDIR)/fallout_hack.cpp

$(BUILDDIR)/game.o: $(SRCDIR)/FalloutGame.cpp $(INCDIR)/FalloutGame.h $(INCDIR)/FalloutText.h $(INCDIR)/FalloutWords.h
	$(CC) $(CCFLAGS) -o $(BUILDDIR)/game.o $(SRCDIR)/FalloutGame.cpp

$(BUILDDIR)/text.o: $(SRCDIR)/FalloutText.cpp
	$(CC) $(CCFLAGS) -o $(BUILDDIR)/text.o $(SRCDIR)/FalloutText.cpp

$(BUILDDIR)/words.o: $(SRCDIR)/FalloutWords.cpp
	$(CC) $(CCFLAGS) -o $(BUILDDIR)/words.o $(SRCDIR)/FalloutWords.cpp
	
$(BUILDDIR)/display.o: $(SRCDIR)/FalloutDisplay.cpp
	$(CC) $(CCFLAGS) -o $(BUILDDIR)/display.o $(SRCDIR)/FalloutDisplay.cpp
	
$(BUILDDIR)/cursor.o: $(SRCDIR)/FalloutCursor.cpp
	$(CC) $(CCFLAGS) -o $(BUILDDIR)/cursor.o $(SRCDIR)/FalloutCursor.cpp

clean:
	rm $(BUILDDIR)/*.o $(BINDIR)/fallout_hack
