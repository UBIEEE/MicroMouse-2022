#include "test.h"

void *test1(cell, FILE *input_file);

//************
//TESTING FILE
//************

// Algorithm was simulated 1,000,000 times and the largest the stack ever got was 38
cell stack[STACK_LENGTH];
// Index where the top of the stack is
int top_of_stack = 0;

// typedef struct 
// {
//     uint8_t status; //  first 4 - Boarder last 4 - parents
//     uint8_t position; // first 4 - x       last 4 - y
// } cell;


cell testCell = { 0b11100001, 0b11111111}; //3 boarders and 1 neighbor 
void *test1(cell testCell, FILE *input_file){
    FILE *var = (input_file == NULL) ? stderr : input_file;

if(has_top_border(testCell) == true){ //Has a 1 in the first bit
    fprintf(var, "True");
}else{
    fprintf(var, "error on top");
}

if(has_bottom_border(testCell) == true){ //Has a 1 in the second bit
        fprintf(var, "True");
}else{
    fprintf(var, "error on bottom");
}

if(has_right_border(testCell) == true){//Has a 1 in the third bit
    fprintf(var, "True");
}else{
    fprintf(var, "error on right");
}

if(has_left_border(testCell) != true){ //Has a 0 in the fourth bit
        fprintf(var, "True");
}else{
    fprintf(var, "error on left");
}
}//end of method
