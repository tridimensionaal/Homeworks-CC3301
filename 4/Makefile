CFLAGS= -g -Wall -pedantic -std=c99

all: compactar

compactar: compactar.c
	gcc $(CFLAGS) -o compactar compactar.c

test-g:
	make clean
	make
	./verificar compactar dicc-orig.txt dicc.txt dicc-out.txt
	./verificar compactar dicc2-orig.txt dicc2.txt dicc2-out.txt

test-O:
	make clean
	make "CFLAGS=-O -Wall -pedantic -std=c99"
	./verificar compactar dicc2-orig.txt dicc.txt dicc2-out.txt

test-O-m32:
	make clean
	make "CFLAGS=-O -m32 -Wall -pedantic -std=c99" "LDFLAGS=-m32"
	./verificar compactar dicc-orig.txt dicc.txt dicc-out.txt

test-valgrind:
	make clean
	make CFLAGS="-g -Wall -pedantic -std=c99"
	cp dicc2-orig.txt dicc2.txt
	bash -c 'valgrind ./compactar dicc2.txt |& tee run.log'
	cmp dicc2.txt dicc2-out.txt
	echo
	echo "Examine el reporte de valgrind en el archivo run.log"

test-valgrind-ddd:
	make clean
	make "CFLAGS=-g -Wall -pedantic -std=c99"
	cp dicc-orig.txt dicc.txt
	valgrind --vgdb=yes --vgdb-error=0 ./compactar dicc.txt

clean:
	rm -f *.o compactar
