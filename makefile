# Make file for arduino
# TODO also is this a c or c++ project, we are using the c++ compiler

test: helloWorld.c
	g++ -o hello helloWorld.c 
	./hello
PHONY: clean

helpers: helpers.c
	g++ -o helpers helpers.c
	./helpers
PHONY: clean

algorithm: algorithm.c
	g++ -o runner.c algorithm.h algorithm.c
	./algorithm
PHONY: clean

clean:
	rm -f hello
	rm -f helpers
	rm -f algorithm
