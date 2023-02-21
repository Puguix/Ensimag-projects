CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -I../include
# truc cracra pour récupérer le chemin absolu vers le répertoire lib/
LIBDIR = $(shell dirname $(shell find $(shell pwd) | head -n 1))/lib/
LDFLAGS = -Wl,-rpath=$(LIBDIR) -L$(LIBDIR) -ldirectory

TESTS = directory-01-test \
	directory-02-test \
	directory-03-test \
	directory-04-test \
	directory-05-test \
	directory-06-test \
	directory-07-test
SRC = $(TESTS:=.c)
OBJ = $(TESTS:=.o)

all: $(TESTS)

%-test: %.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

.PHONY: clean

clean:
	rm -rf *.o *~ $(TESTS)