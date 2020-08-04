OBJS    = tests.o linkedList.o node.o stack.o
SOURCE  = tests.c linkedList.c node.c stack.c
HEADER  = linkedList.h node.h stack.h queue.h
OUT = tests
CC  = gcc -g
LINT =
FLAGS    = -std=c89 -c -Wall -Wextra
LFLAGS   =

debug: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(LFLAGS)

rel: $(OBJS)
	$(CC) -O3 $(OBJS) -o $(OUT) $(LFLAGS)

%.o: %.c
	$(CC) $(FLAGS) $< -o $@

install: linkedList.o
	cp linkedList.o /usr/local/lib/
	cp linkedList.h /usr/local/include/

uninstall:
	rm /usr/local/lib/linkedList.o
	rm /usr/local/include/linkedList.h

clean:
	rm -f $(OBJS) $(OUT)

valgrind: $(OUT)
	valgrind $(OUT)

valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)
