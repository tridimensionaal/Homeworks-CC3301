CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g

all: test

t3.o test-t3.o: t3.h

test-t3: t3.o test-t3.o

test:
	make clean
	make test-t3

test-g:
	make clean
	make test-t3
	./test-t3

test-O:
	make clean
	make "CFLAGS=-O -Wall -pedantic -std=c99" test-t3
	./test-t3

test-O-m32:
	make clean
	make "CFLAGS=-O -m32 -Wall -pedantic -std=c99" "LDFLAGS=-m32" test-t3
	./test-t3

test-valgrind:
	make clean
	make "CFLAGS=-DVALGRIND -g -Wall -pedantic -std=c99" test-t3
	bash -c 'valgrind ./test-t3 |& tee test-t3.log'
	echo
	echo "Examine el reporte de valgrind en el archivo test-t3.log"

test-valgrind-ddd:
	make clean
	make "CFLAGS=-DVALGRIND -g -Wall -pedantic -std=c99" test-t3
	valgrind --vgdb=yes --vgdb-error=0 ./test-t3

clean:
	rm -f *.o
	rm -f test-t3
