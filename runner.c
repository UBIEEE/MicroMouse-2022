/* 
    Runner for the algorithm process to serve as a starting place
    for our threads and whatever
*/
#include <stdio.h>
#include "helpers.h"
#include "algorithm.h"


int main(int argc, char *argv[]) {

    // Command Line parsing??? 
    fprintf(stderr, "running our algorithm");
    algorithm();
    return 0;
}