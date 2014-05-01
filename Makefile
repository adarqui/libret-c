deps:
	echo "No dependencies."

all:
	echo "Nothing to build."

test:
	gcc -I./include -Wall test.c -o run-tests -lcunit
	./run-tests

install:
	cp include/ret.h /usr/include/ret.h
