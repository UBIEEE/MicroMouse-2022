# Make file for arduino
# TODO also is this a c or c++ project, we are using the c++ compiler
COMPILER = clang

clean:
	rm -f helpers
	rm -f algo

algo:
	$(COMPILER) -o algo ./runner.c ./lib/helpers.c ./algos/algorithm.c
	./algo
PHONY: all

all: algo helpers
	make clean
	make algo
