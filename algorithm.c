
// helper functions to implement


#define MAZE_SIZE 16

// is_destination()
bool is_destination(cell current_cell)
{
    int cx = get_x(current_cell);
    int cy = get_y(current_cell);

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



// find_valid_neighbors()
    // find_any_neighbors()
        // where_is_neighbors()

// optimize_neighbor_order()
