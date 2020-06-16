OBJS	= tests.o linkedList.o
SOURCE	= tests.c linkedList.c
HEADER	= linkedList.h
OUT	= tests
CC	= gcc -g
FLAGS    = -std=c89 -c -Wall
LFLAGS	 =

debug: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(LFLAGS)

linkedList.o: linkedList.c
	$(CC) $(FLAGS) linkedList.c

rel: $(OBJS)
	$(CC) -O3 $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

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
