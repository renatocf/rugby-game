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
#define DIR_UP         (direction_t){-1,  0}
#define DIR_UP_RIGHT   (direction_t){-1,  1}
#define DIR_RIGHT      (direction_t){ 0,  1}
#define DIR_DOWN_RIGHT (direction_t){ 1,  1}
#define DIR_DOWN       (direction_t){ 1,  0}
#define DIR_DOWN_LEFT  (direction_t){ 1, -1}
#define DIR_LEFT       (direction_t){ 0, -1}
#define DIR_UP_LEFT    (direction_t){-1, -1}

#endif // DIRECTION_H
