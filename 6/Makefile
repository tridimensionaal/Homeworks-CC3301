CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g
LDLIBS= -lpthread

all: test-t6

test-t6.o t6.o: t6.h

test-t6: t6.o test-t6.o

test-g:
	make clean
	make
	./test-t6

test-O:
	make clean
	make "CFLAGS= -O -Wall -pedantic -std=c99" LDFLAGS=
	./test-t6

test-O-m32:
	make clean
	make "CFLAGS= -m32 -O -Wall -pedantic -std=c99" "LDFLAGS=-m32"
	./test-t6

test-valgrind-ddd:
	make clean
	make "CFLAGS=-g -Wall -pedantic -std=c99 -DVALGRIND"
	valgrind --vgdb=yes --vgdb-error=0 ./test-t6

test-valgrind:
	make clean
	make "CFLAGS=-g -Wall -pedantic -std=c99 -DVALGRIND"
	valgrind ./test-t6

test-drd-ddd:
	make clean
	make "CFLAGS=-g -Wall -pedantic -std=c99 -DVALGRIND"
	valgrind --tool=drd --vgdb=yes --vgdb-error=0 ./test-t6

test-sanitize:
	make clean
	make "CFLAGS=-g -fsanitize=thread -Wall -pedantic -std=c99 -DVALGRIND" "LDFLAGS=-fsanitize=thread"
	./test-t6

clean:
	rm -f *.o
	rm -f test-t6
