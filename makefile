# Make file for arduino

test: helloWorld.c
	g++ -o hello helloWorld.c 
	./hello
PHONY: clean

helpers: helpers.c
	g++ -o helpers helpers.c
	./helpers
PHONY: clean

algorithm: algorithm.c
	g++ -o algorithm algorithm.c
	./algorithm
PHONY: clean

clean:
	rm -f hello
	rm -f helpers
	rm -f algorithm
