CC = clang
CFLAGS = -Wall -Wextra -std=c99 -g -lpthread
LFLAGS = 
LIBS = -lm -D_GNU_SOURCE 
SOURCES = q4.c
OUTPUT = out
OBJECTS = $(subst .c,.o,$(SOURCES))
BIN = $(OBJECTS)
.PHONY: clean help

$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

all : $(BIN)

clean:
	rm -f $(OBJECTS) $(BIN) $(OUTPUT) *~

help:
	@echo "Valid targets:"
	@echo "  clean:  removes .o and binary files"
