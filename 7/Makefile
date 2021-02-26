CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g
LDLIBS= -lm

all: test-t7

test-t7.o t7.o: viajante.h

test-t7: t7.o test-t7.o

test-g:
	make clean
	make
	./test-t7

test-O:
	make clean
	make "CFLAGS= -O -Wall -pedantic -std=c99" LDFLAGS=
	./test-t7

test-O-m32:
	make clean
	make "CFLAGS= -m32 -O -Wall -pedantic -std=c99" "LDFLAGS=-m32"
	./test-t7

test-valgrind-ddd:
	make clean
	make "CFLAGS=-g -Wall -pedantic -std=c99 -DVALGRIND"
	valgrind --vgdb=yes --vgdb-error=0 ./test-t7

test-valgrind:
	make clean
	make "CFLAGS=-g -Wall -pedantic -std=c99 -DVALGRIND"
	valgrind ./test-t7

clean:
	rm -f *.o
	rm -f test-t7
