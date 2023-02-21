CC = gcc
LD = gcc
CFLAGS = -Wall -Wextra -g -O2 -Iinclude/ -fPIC

all: lib/libdirectory.so build-tests

lib/libdirectory.so: obj/directory.o obj/contact.o obj/hash.o
	$(CC) -shared $^ -o $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

build-tests:
	make -C tests/

.PHONY: clean

clean:
	rm -rf obj/*.o lib/libdirectory.so
	make -C tests/ clean

