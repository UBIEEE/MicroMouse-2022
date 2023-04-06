#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "helpers.h"

typedef struct 
{
    uint8_t status;
    uint8_t position;
} cell;

#define STACK_LENGTH 40
// Algorithm was simulated 1,000,000 times and the largest the stack ever got was 38
cell stack[STACK_LENGTH];
// Index where the top of the stack is
int top_of_stack = 0;

bool push(cell c)
{
    if (top_of_stack >= STACK_LENGTH) return false;

    top_of_stack++;
    stack[top_of_stack] = c;
    return true;
}

cell pop()
{
    // if (top_of_stack <= 0) return;

    cell c = stack[top_of_stack];
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

int main(void)
{
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