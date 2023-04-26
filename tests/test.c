#include "../src/helpers.h"
#include "../src/algorithm.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//************
//TESTING FILE
//************

#define STACK_LENGTH 40
// Algorithm was simulated 1,000,000 times and the largest the stack ever got was 38
cell stack[STACK_LENGTH];
// Index where the top of the stack is
int top_of_stack = 0;

// typedef struct 
// {
//     uint8_t status; //  first 4 - Boarder last 4 - parents
//     uint8_t position; // first 4 - x       last 4 - y
// } cell;

cell testCell = { 0b11100001, 0b11111111} //3 boarders and 1 neighbor 

if(has_top_border(testCell) == true){ //Has a 1 in the first bit
    return true
}else{
    return false
}

if(has_bottom_border(testCell) == true){ //Has a 1 in the second bit
    return true 
}else{
    return false
}

if(has_right_border(testCell) == true){//Has a 1 in the third bit
    return true  
}else{
    return false
}

if(has_left_border(testCell) != true){ //Has a 0 in the fourth bit
    return true 
}else{
    return false
}
