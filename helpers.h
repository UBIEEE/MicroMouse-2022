#ifndef HELPERS_FILE
#define HELPERS_FILE

#include <stdint.h>
#include <stdbool.h>

/***********************************
 * Cell representation functionality
 * *********************************/
typedef struct 
{
    uint8_t status;
    uint8_t position;
} cell;

bool push(cell c);

cell pop();

bool has_top_border(cell c);

bool has_bottom_border(cell c);

bool has_right_border(cell c);

bool has_left_border(cell c);

bool is_visited(cell c);

bool top_is_parent(cell c);

bool bottom_is_parent(cell c);

bool right_is_parent(cell c);

bool left_is_parent(cell c);

bool has_parent(cell c);

uint8_t get_x(cell c);

uint8_t get_y(cell c);

void remove_left_wall(cell *input);

void remove_right_wall(cell *input);

void remove_top_wall(cell *input);

void remove_bottom_wall(cell *input);

void set_top_as_parent(cell *input);

void set_bottom_as_parent(cell *input);

void set_right_as_parent(cell *input);

void set_left_as_parent(cell *input);

uint8_t make_position_coordinates(int y, int x);


#endif