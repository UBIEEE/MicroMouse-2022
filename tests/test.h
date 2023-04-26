#ifndef TESTING_H
#define TESTING_H


#include "../src/helpers.h"
#include "../src/algorithm.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Holds the testing flags that we want to pass into our testing
typedef struct Flags {
    // Add some flags for testing
    bool helpers; // Testing for the helpers function 
}flags;

// Holds information about test
typedef struct Test {
    int testNum;
    char *testDesc;
}test;


// Can be thrown in the case we are segfaulting
void panic(FILE *input_file, char *message);

#endif