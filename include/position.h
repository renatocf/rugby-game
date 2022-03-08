#ifndef POSITION_H
#define POSITION_H

// Standard headers
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

// Internal headers
#include "direction.h"

// Structs

/**
 * A position represents where an object is in a 2D grid.
 */
struct position {
  size_t i;
  size_t j;
};
typedef struct position position_t;

// Macros
#define INVALID_POSITION { ULONG_MAX, ULONG_MAX }

// Functions
bool equal_positions(position_t p1, position_t p2);
bool neighbor_positions(position_t center, position_t candidate);
position_t move_position(position_t current_position, direction_t direction);

#endif // POSITION_H
