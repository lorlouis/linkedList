OBJS    = node.o linkedList.o stack.o
SOURCE  = node.c linkedList.c stack.c
HEADER  = linkedList.h node.h stack.h queue.h
OUT = liblinkedList.a
CC  = gcc -g
LINT =
FLAGS = -m64 -std=c99 -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes
LFLAGS =

debug: $(OBJS)
	ar rcs $(OUT) $(OBJS)
	$(CC) tests.c -o tests $(FLAGS) -L. -llinkedList

rel: $(OBJS)
	ar rcs $(OUT) $(OBJS)
	mkdir -p lib
	cp $(OUT) lib/
	mkdir -p include
	mkdir -p include/ll
	cp $(HEADER) include/ll/

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(OUT) tests
	rm -rf lib/ include/

valgrind: $(OUT)
	valgrind $(OUT)

valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)
