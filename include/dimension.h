#ifndef DIMENSION_H
#define DIMENSION_H

// Standard headers
#include <stddef.h>

// Structs

/**
 * A dimension represents the number of lines and columns in a 2D grid.
 */
struct dimension {
  size_t height;
  size_t width;
};
typedef struct dimension dimension_t;

// Macros
#define NULL_DIMENSION { 0, 0 }

#endif // DIMENSION_H
