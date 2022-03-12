#ifndef FIELD_H
#define FIELD_H

// Standard headers
#include <stdbool.h>

// Internal headers
#include "dimension.h"
#include "position.h"
#include "item.h"

// Structs

/**
 * A field is a 2D grid where a list of items are positioned.
 */
typedef struct field* Field;

// Macros
#define FIELD_MIN_DIMENSION (dimension_t) { 3, 3 }

// Functions
Field new_field(dimension_t dimension);
void delete_field(Field field);

dimension_t get_field_dimension(Field field);

void print_field_info(Field field);
void print_field_grid(Field field);

void add_item_to_field(Field field, Item item, position_t position);
void move_item_in_field(Field field, Item item, direction_t direction);

#endif // FIELD_H
