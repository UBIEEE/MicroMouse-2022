/* 
    Runner for the algorithm process to serve as a starting place
    for our threads and whatever
*/
#include <stdio.h>
#include "lib/helpers.h"
#include "algos/algorithm.h"


int main(int argc, char *argv[]) {

    // Command Line parsing???
    fprintf(stderr, "running our algorithm\n");
    algorithm();
    return 0;
}


void testing(){
        // Using main for testing

    // Was testing setup of the default array
    
    cell grid[16][16];

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            cell c;
            c.status = 0b11110000;
            c.position = make_position_coordinates(y, x);
            grid[y][x] = c;
        }
    }

    cell a = {0b11110000, 0b00000000};
    cell b = {0b11110000, 0b00000001};
    cell c = {0b11110000, 0b00000010};
    cell d = {0b11110000, 0b00000011};

    push(a);
    push(b);
    push(c);
    push(d);

    
    printf("Info for a: X: %i Y: %i\n", get_x(a), get_y(a));
    printf("Info for b: X: %i Y: %i\n", get_x(b), get_y(b));
    printf("Info for c: X: %i Y: %i\n", get_x(c), get_y(c));
    printf("Info for d: X: %i Y: %i\n", get_x(d), get_y(d));

    cell result = pop();
    printf("Info for popped cell 1: X: %i Y: %i\n", get_x(result), get_y(result));

    result = pop();
    printf("Info for popped cell 2: X: %i Y: %i\n", get_x(result), get_y(result));

    result = pop();
    printf("Info for popped cell 3: X: %i Y: %i\n", get_x(result), get_y(result));

    result = pop();
    printf("Info for popped cell 4: X: %i Y: %i\n", get_x(result), get_y(result));
}