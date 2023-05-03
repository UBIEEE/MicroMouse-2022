#include "helpers.h"
#include "algorithm.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAZE_SIZE 16

// extern cell *neighbors;

bool cells_are_same(cell current, cell comparee)
{
    if ((current.position == comparee.position) && (current.status == comparee.status))
    {
        return true;
    }
    return false;
}

// is_destination()
bool is_destination(cell current_cell)
{
    uint8_t cx = get_x(current_cell);
    uint8_t cy = get_y(current_cell);

    int goals[2] = { ((MAZE_SIZE/2) - 1), MAZE_SIZE};

    bool bx = false;
    bool bOOBy = false;

    // check if cx and cy are inside of goals
    for (int i = 0; i < 2; i++)
    {
        if (cx == goals[i])
        {
            bx = true;
        }
        if (cy == goals[i])
        {
            bOOBy = true;
        }
    }

    if (bx && bOOBy)
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

    if ((cy == ty) && (cx == tx + 1) && (has_left_border(current_cell) == false))
    {
        return true;
    }
    else if ((cy == ty) && (cx + 1 == tx) && (has_right_border(current_cell) == false))
    {
        return true;
    }
    else if ((cx == tx) && (cy + 1 == ty) && (has_bottom_border(current_cell) == false))
    {
        return true;
    }
    else if ((cx == tx) && (cy == ty + 1) && (has_top_border(current_cell) == false))
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
        fprintf(stderr, "Something happened neighbors aren't bordering each other");
    }
    return ret;
}


int manhattan_distance(cell location)
{
    int goal_lower = (MAZE_SIZE/2) - 1;
    int goal_upper = MAZE_SIZE/2;

    int lc_x = get_x(location);
    int lc_y = get_y(location);

    int tc_x;
    int tc_y;

    // for x
    if (abs(lc_x - goal_lower) < abs(lc_x - goal_upper))
    {
        tc_x = goal_lower;
    }
    else
    {
        tc_x = goal_upper;
    }

    // for y
    if (abs(lc_y - goal_lower) < abs(lc_y - goal_upper))
    {
        tc_y = goal_lower;
    }
    else
    {
        tc_y = goal_upper;
    }

    int dx = abs(tc_x - lc_x);
    int dy = abs(tc_y - lc_y);

    int total_manhattan_distance = dx + dy;
    return total_manhattan_distance;

}


bool neighbor_is_reachable(cell current, cell neighbor)
{
    if(is_visited(neighbor))
    {
        char *where_is = where_is_neighbor(&current, &neighbor);
        if ((strcmp(where_is, "Above") == 0) && (has_top_border(current) == false))
        {
            return true;
        } 
        else if ((strcmp(where_is, "Right") == 0) && (has_right_border(current) == false))
        {
            return true;
        }
        else if ((strcmp(where_is, "Left") == 0) && (has_left_border(current) == false))
        {
            return true;
        }
        else if ((strcmp(where_is, "Below") == 0) && (has_bottom_border(current) == false))
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
}

void find_valid_neighbors_sorted(cell current, cell** grid)
{

    // Implementing found neighbors portion of the code: 

    cell *valid_neighbors[4]; // there can only ever be a maximum of 4 neighbors
    
    int current_valid_neighbor_index = 0;

    int cx = get_x(current);
    int cy = get_y(current);

    //int range = {-1, 0, 1};
    for (int xbump = -1; xbump < 2; xbump++)
    {
        for (int ybump = -1; ybump < 2; ybump++)
        {

            int y_index = cy + ybump;
            int x_index = cx + xbump;
            if (
                // Abs conditional will only pass cells that are at indexes that can be neighbors (n)
                // BnB
                // nCn
                // BnB
                (abs(ybump) != abs(xbump)) 
                && (y_index >= 0) // Not out of bounds in the array
                && (y_index <= MAZE_SIZE - 1)
                && (x_index >= 0)
                && (x_index <= MAZE_SIZE - 1)
            ){
                
                // add neighbor found to array if it is valid
                cell neighbor = grid[y_index][x_index];
                if (neighbor_is_reachable(current, neighbor))
                {
                    valid_neighbors[current_valid_neighbor_index] = &grid[y_index][x_index]; // HOW ARE WE INDEXING INTO GRID?
                    current_valid_neighbor_index++;
                }
                
            }
        }
    }

    // Sort the array in terms of the manhattan distance so that the closest cells are at the end of the array
    // Implement a selection sort on the valid_neighbors array using the manhattan distance as the value to sort bOOBy

    for (int i = 0; i < current_valid_neighbor_index; i++)
    {
        int largest_val = manhattan_distance(*valid_neighbors[i]);
        int largest_index = i;
        for (int j = i; j < current_valid_neighbor_index; j++)
        {
            if ((manhattan_distance(*valid_neighbors[j]) + 1) > largest_val)
            {
                largest_val = manhattan_distance(*valid_neighbors[j]) + 1;
                largest_index = j;
            }
        }

        // Swap values
        cell *temp = valid_neighbors[i];
        valid_neighbors[i] = valid_neighbors[largest_index];
        valid_neighbors[largest_index] = temp;
    }

    // Add the neighbors to the stack, starting at the beginning
    for (int i = 0; i < current_valid_neighbor_index; i++)
    {
        push(valid_neighbors[i]);
    }
    
}

cell *movement(cell *current_cell, cell **grid) // gonna need something to represent the mouse aswell
{
    cell *target_cell = pop();

    if (cells_are_same(*current_cell,*target_cell))
    {
        // set the current cell as visited and update the grid with the information
        sensing(); // sensing function needs to be implemented
    }

    while ((cells_are_same(*current_cell, *target_cell) == false) && (are_valid_neighbors(*current_cell, *target_cell) == false))
    {
        reorient_by_cell(current_cell, get_parent(*current_cell, grid)); // needs to be implemented

        sensing(); // maybe?

        move_forward(); // was move by cell

        sensing(); // maybe?

        current_cell = get_parent(*current_cell, grid); // get_parent function needs to be implemented

    }

    if (are_valid_neighbors(*current_cell, *target_cell))
    {
        set_parentage(target_cell, current_cell);

        reorient_by_cell(current_cell, target_cell);

        sensing(); // maybe?

        current_cell = target_cell;

        move_forward(); // was move by cell

        sensing(); // maybe?
    }

    find_valid_neighbors_sorted(*current_cell, grid);

    return current_cell; // maybe not needed, might turn into a void function
}

void algorithm(){
    fprintf(stderr, "This algorithm can print things\n");
}