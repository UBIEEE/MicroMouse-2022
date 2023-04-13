# Make file for arduino
# TODO also is this a c or c++ project, we are using the c++ compiler


helpers: helpers.c
	g++ -o helpers helpers.c
	./helpers
PHONY: clean

algo: algorithm.c
	g++ -o algo runner.c helpers.c algorithm.c
	./algo
PHONY: clean

clean:
	rm -f helpers
	rm -f algo
