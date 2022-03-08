// Standard headers
#include <stdbool.h>
#include <stdio.h>

// Main header
#include "position.h"

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

bool equal_positions(position_t p1, position_t p2) {
  return p1.i == p2.i && p1.j == p2.j;
}

/*----------------------------------------------------------------------------*/

bool neighbor_positions(position_t center, position_t candidate) {
  return candidate.i >= center.i-1 && candidate.i <= center.i+1
    && candidate.j >= center.i-1 && candidate.j <= center.j+1;
}

/*----------------------------------------------------------------------------*/

position_t move_position(position_t current_position, direction_t direction) {
  position_t new_position = {
    current_position.i + direction.i,
    current_position.j + direction.j
  };

  return new_position;
}

/*----------------------------------------------------------------------------*/
