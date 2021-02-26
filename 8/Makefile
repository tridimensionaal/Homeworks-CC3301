CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g
LDLIBS= -lm

all: test-t8a test-t8b

test-t8.o t8a.o t8b.o: viajante.h

test-t8a: t8a.o test-t8.o
	gcc $(LDFLAGS) t8a.o test-t8.o -o test-t8a $(LDLIBS)

test-t8b: t8b.o test-t8.o
	gcc $(LDFLAGS) t8b.o test-t8.o -o test-t8b $(LDLIBS)

test-O:
	make clean
	make "CFLAGS= -O3 -Wall -pedantic -std=c99" "LDFLAGS="
	echo Ejecute manualmente ./test-t8a y ./test-t8b

clean:
	rm -f *.o
	rm -f test-t8a test-t8b
