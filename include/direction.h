#ifndef DIRECTION_H
#define DIRECTION_H

// Structs

/**
 * A direction represents a vector of movement in a 2D grid.
 */
struct direction {
  int i;
  int j;
};
typedef struct direction direction_t;

// Macros
#define DIR_STAY       {  0,  0 }
#define DIR_UP         { -1,  0 }
#define DIR_UP_RIGHT   { -1,  1 }
#define DIR_RIGHT      {  0,  1 }
#define DIR_DOWN_RIGHT {  1,  1 }
#define DIR_DOWN       {  1,  0 }
#define DIR_DOWN_LEFT  {  1, -1 }
#define DIR_LEFT       {  0, -1 }
#define DIR_UP_LEFT    { -1, -1 }

#endif // DIRECTION_H
