
#include "test.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Can be thrown in the case we are segfaulting
void panic(FILE *input_file, char *message){
    FILE *fptr = (input_file == NULL) ? stderr : input_file;
    fprintf(fptr, message);
    exit(1);
    return;
}