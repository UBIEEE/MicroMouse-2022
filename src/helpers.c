#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "helpers.h"

#define STACK_LENGTH 40
// Algorithm was simulated 1,000,000 times and the largest the stack ever got was 38
cell *stack[STACK_LENGTH];
// Index where the top of the stack is
int top_of_stack = 0;

bool push(cell *c)
{
    if (top_of_stack >= STACK_LENGTH) return false;

    top_of_stack++;
    stack[top_of_stack] = c;
    return true;
}

cell * pop()
{
    // if (top_of_stack <= 0) return;

    cell *c = stack[top_of_stack];
    top_of_stack--;
    return c;

}

bool has_top_border(cell c)
{
    uint8_t input = c.status;
    uint8_t key = 0b10000000;
    uint8_t result = (input & key);

    if (result == key)
    {
        return true;
    }
    return false;
}

bool has_bottom_border(cell c)
{
    uint8_t input = c.status;
    uint8_t key = 0b01000000;
    uint8_t result = (input & key);

    if (result == key)
    {
        return true;
    }
    return false;
}

bool has_right_border(cell c)
{
    uint8_t input = c.status;
    uint8_t key = 0b00100000;
    uint8_t result = (input & key);

    if (result == key)
    {
        return true;
    }
    return false;
}

bool has_left_border(cell c)
{
    uint8_t input = c.status;
    uint8_t key = 0b00010000;
    uint8_t result = (input & key);

    if (result == key)
    {
        return true;
    }
    return false;
}

bool is_visited(cell c)
{
    if (!(has_top_border(c) && has_bottom_border(c) && has_right_border(c) && has_left_border(c)))
    {
        return true;
    }
    return false;
}

bool top_is_parent(cell c)
{
    uint8_t input = c.status;
    uint8_t key = 0b00001000;
    uint8_t result = (input & key);
    if (result == key)
    {
        return true;
    }
    return false;

}

bool bottom_is_parent(cell c)
{
    uint8_t input = c.status;
    uint8_t key = 0b00000100;
    uint8_t result = (input & key);

    if (result == key)
    {
        return true;
    }
    return false;
}

bool right_is_parent(cell c)
{
    uint8_t input = c.status;
    uint8_t key = 0b00000010;
    uint8_t result = (input & key);
    if (result == key)
    {
        return true;
    }
    return false;
}

bool left_is_parent(cell c)
{
    uint8_t input = c.status;
    uint8_t key = 0b00000001;
    uint8_t result = (input & key);

    if (result == key)
    {
        return true;
    }
    return false;
}

bool has_parent(cell c)
{
    if (top_is_parent(c) || bottom_is_parent(c) || right_is_parent(c) || left_is_parent(c))
    {
        return true;
    }
    return false;
}

uint8_t get_x(cell c)
{
    uint8_t pos = c.position;
    pos = pos & 0b11110000;
    uint8_t result = pos >> 4;
    return result;
}

uint8_t get_y(cell c)
{
    uint8_t pos = c.position;
    pos = pos & 0b00001111;
    uint8_t result = pos;
    return result;
}

void remove_top_wall(cell *input)
{
    // Change the value of input.pos by these steps:
    // 1. Negate input
    // 2. OR result of negation with key
    // 3. Negate result

    uint8_t state = (*input).status;
    state = ~state;
    state = state | 0b10000000;
    state = ~state;
    (*input).status = state;
}

void remove_bottom_wall(cell *input)
{
    // Change the value of input.pos by these steps:
    // 1. Negate input
    // 2. OR result of negation with key
    // 3. Negate result

    uint8_t state = (*input).status;
    state = ~state;
    state = state | 0b01000000;
    state = ~state;
    (*input).status = state;
}

void remove_right_wall(cell *input)
{
    // Change the value of input.pos by these steps:
    // 1. Negate input
    // 2. OR result of negation with key
    // 3. Negate result

    uint8_t state = (*input).status;
    state = ~state;
    state = state | 0b00100000;
    state = ~state;
    (*input).status = state;
}

void remove_left_wall(cell *input)
{
    // Change the value of input.pos by these steps:
    // 1. Negate input
    // 2. OR result of negation with key
    // 3. Negate result

    uint8_t state = (*input).status;
    state = ~state;
    state = state | 0b00010000;
    state = ~state;
    (*input).status = state;
}

void set_top_as_parent(cell *input)
{
    uint8_t state = (*input).status;
    uint8_t key = 0b00001000;
    (*input).status = state | key;
}

void set_bottom_as_parent(cell *input)
{
    uint8_t state = (*input).status;
    uint8_t key = 0b00000100;
    (*input).status = state | key;
}

void set_right_as_parent(cell *input)
{
    uint8_t state = (*input).status;
    uint8_t key = 0b00000010;
    (*input).status = state | key;
}

void set_left_as_parent(cell *input)
{
    uint8_t state = (*input).status;
    uint8_t key = 0b00000001;
    (*input).status = state | key;
}

// Both position coordinates are held in one uint8_t with xxxxyyyy
uint8_t make_position_coordinates(int y, int x)
{
    uint8_t x_val = (uint8_t) x;
    x_val = x_val << 4;
    uint8_t y_val = (uint8_t) y;
    uint8_t result = x_val | y_val;
    cell r;
    r.status = 0b11110000;
    r.position = result;
    // printf("Y Cord: %i, X Cord: %i \n", get_y(r), get_x(r));

    return result;

}

cell *get_parent(cell current, cell** grid)
{
    int cx = get_x(current);
    int cy = get_y(current);

    int px = cx;
    int py = cy;

    if (right_is_parent(current))
    {
        px++;
    }
    else if (left_is_parent(current))
    {
        px--;
    }
    else if (top_is_parent(current))
    {
        py++;
    }
    else if (bottom_is_parent(current))
    {
        py--;
    }

    cell *parent = &grid[py][px]; // how are we indexing into the grid?

    return parent;
}

void set_parentage(cell *changee, cell *parent)
{
    int cx = get_x(*changee);
    int cy = get_y(*changee);
    int px = get_x(*parent);
    int py = get_y(*parent);

    if ((cy == py) && (cx == px +1))
    {
        // Parent is to left
        set_left_as_parent(&changee);
        return;
    }
    else if ((cy == py) && (cx+1 == px))
    {
        // Parent is to right
        set_right_as_parent(&changee);
        return;
    }
    else if ((cx == px) && (cy == py +1))
    {
        // Parent is on top
        set_top_as_parent(&changee);
        return;
    }
    else if ((cx == px) && (cy + 1 == py))
    {
        // Parent is on bottom
        set_bottom_as_parent(&changee);
        return;
    }
    fprintf(stderr, "Error in set_parent: Changee and parent were not next to each other!");
    return;
    
}