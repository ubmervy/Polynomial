# working dirs

SRCDIR = ./src
BUILDDIR = ./obj/Debug

CC=g++

CFLAGS=-std=c++11 -I./include -c -Wall -Wno-unused-value -Wno-narrowing

LDFLAGS=

EXECUTABLE=main
SOURCES=$(SRCDIR)/main.cpp
OBJECTS = $(BUILDDIR)/main.o

all: $(EXECUTABLE)
  
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(EXECUTABLE) ${OBJECTS}

