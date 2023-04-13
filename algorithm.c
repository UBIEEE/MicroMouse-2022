
// helper functions to implement
#include "helpers.h"
#include "algorithm.h"
#include <stdbool.h>
#include <stdio.h>

#define MAZE_SIZE 16

extern cell *neighbors;

// is_destination()
bool is_destination(cell current_cell)
{
    uint8_t cx = get_x(current_cell);
    uint8_t cy = get_y(current_cell);

    int goals[2] = { ((MAZE_SIZE/2) - 1), MAZE_SIZE};

    bool bx = false;
    bool by = false;

    // check if cx and cy are inside of goals
    for (int i = 0; i < 2; i++)
    {
        if (cx == goals[i])
        {
            bx = true;
        }
        if (cy == goals[i])
        {
            by = true;
        }
    }

    if (bx & by)
    {
        return true;
    }
    return false;

}

// are_valid_neighbors()
bool are_valid_neighbors(cell current_cell, cell target_cell)
{
    int cx = get_x(current_cell);
    int cy = get_y(current_cell);
    int tx = get_x(target_cell);
    int ty = get_y(target_cell);

    if ((cy == ty) & (cx == tx + 1) & (has_left_border(current_cell) == false))
    {
        return true;
    }
    else if ((cy == ty) & (cx + 1 == tx) & (has_right_border(current_cell) == false))
    {
        return true;
    }
    else if ((cx == tx) & (cy + 1 == ty) & (has_bottom_border(current_cell) == false))
    {
        return true;
    }
    else if ((cx == tx) & (cy == ty + 1) & (has_top_border(current_cell) == false))
    {
        return true;
    }
    else 
    {
        return false;
    }
}

// takes the current cell and determines the input cell
char *where_is_neighbor(cell *current,cell *neighbor){
    char * ret = "None found";
    uint8_t cx = get_x(*current);
    uint8_t cy = get_y(*current);
    uint8_t nx = get_x(*neighbor);
    uint8_t ny = get_y(*neighbor);
    if ((cy == ny) && (cx == nx +1)){
        ret = "Left";
    }
    if ((cy == ny) && (cx+1 == nx)){
        ret = "Right";
    }
    if ((cx == nx) && (cy == ny +1)){
        ret = "Above";
    }
    if ((cx == nx) && (cy + 1 == ny)){
        ret = "Below";
    }
    if ( ret == "None found"){
        // In the case something goes wrong we will get an error message here
        fprintf(stderr, "Something happened neighbors aren't boardering each other");
    }
    return ret;
}



void algorithm(){
    fprintf(stderr, "This algorithm can print things\n");
}

// find_valid_neighbors()
    // find_any_neighbors()
        // where_is_neighbors()

// optimize_neighbor_order()
