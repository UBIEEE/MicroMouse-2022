# Make file for arduino
# TODO also is this a c or c++ project, we are using the c++ compiler

clean:
	rm -f helpers
	rm -f algo

algo: algorithm.c helpers.c
	clang -o algo runner.c helpers.c algorithm.c
	./algo
PHONY: all

all: algo helpers
	make clean
	make algo
