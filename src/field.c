// Standard headers
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Main header
#include "field.h"

/*----------------------------------------------------------------------------*/
/*                        PRIVATE STRUCT IMPLEMENTATION                       */
/*----------------------------------------------------------------------------*/

struct field {
  dimension_t dimension;
  Item** grid;
};

/*----------------------------------------------------------------------------*/
/*                          PRIVATE FUNCTIONS HEADERS                         */
/*----------------------------------------------------------------------------*/

Item** allocate_field_grid(dimension_t dimension);
void free_field_grid(Item** grid, dimension_t dimension);

bool position_is_beyond_limit_of_field(Field field, position_t p);
void print_item_in_field(Item item);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

Field new_field(dimension_t dimension) {
  if (dimension.height < FIELD_MIN_DIMENSION.height) {
    fprintf(stderr,
        "Height must be at least %ld because of the Field's borders\n",
        FIELD_MIN_DIMENSION.height);
    return NULL;
  }

  if (dimension.width < FIELD_MIN_DIMENSION.width) {
    fprintf(stderr,
        "Width must be at least %ld because of the Field's borders\n",
        FIELD_MIN_DIMENSION.width);
    return NULL;
  }

  Field field = malloc(sizeof(*field));

  field->dimension = dimension;
  field->grid = allocate_field_grid(dimension);

  return field;
}

/*----------------------------------------------------------------------------*/

void delete_field(Field field) {
  if (field == NULL) return;

  free_field_grid(field->grid, field->dimension);
  field->grid = NULL;

  field->dimension = (dimension_t) NULL_DIMENSION;

  free(field);
}

/*----------------------------------------------------------------------------*/

dimension_t get_field_dimension(Field field) {
  if (field == NULL) return (dimension_t) NULL_DIMENSION;
  return field->dimension;
}

/*----------------------------------------------------------------------------*/

void print_field_info(Field field) {
  if (field == NULL) return;

  printf("Dimensions (H x W): %ld x %ld\n",
      field->dimension.height, field->dimension.width);
  putchar('\n');
}

/*----------------------------------------------------------------------------*/

void print_field_grid(Field field) {
  if (field == NULL) return;

  for (size_t i = 0; i < field->dimension.height; i++) {
    for (size_t j = 0; j < field->dimension.width; j++) {
      putchar('|');
      print_item_in_field(field->grid[i][j]);
    }
    putchar('|');
    putchar('\n');
  }
  putchar('\n');
}

/*----------------------------------------------------------------------------*/

void add_item_to_field(Field field, Item item, position_t position) {
  if (field == NULL || item == NULL) return;

  if (position_is_beyond_limit_of_field(field, position)) {
    fprintf(stderr, "ERROR: Item '%c' must be within limits of the field!\n",
        get_item_symbol(item));
    return;
  }

  field->grid[position.i][position.j] = item;
  set_item_position(item, position);
}

/*----------------------------------------------------------------------------*/

void move_item_in_field(Field field, Item item, direction_t direction) {
  if (field == NULL || item == NULL) return;

  position_t item_position = get_item_position(item);

  // Given how items are added to the field, their position
  // should never be beyond the limits of the field
  assert(!position_is_beyond_limit_of_field(field, item_position));

  if (!is_item_movable(item)) {
    fprintf(stderr, "WARNING: Item is not movable!\n");
    return;
  }

  position_t new_position = move_position(get_item_position(item), direction);

  // Item cannot be moved if position is already occupied
  if (field->grid[new_position.i][new_position.j] != NULL) return;

  // Change current position in the grid
  field->grid[new_position.i][new_position.j] = item;
  field->grid[item_position.i][item_position.j] = NULL;
  set_item_position(item, new_position);
}

/*----------------------------------------------------------------------------*/
/*                             PRIVATE FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

// Allocate field's grid as C-matrix in the heap
Item** allocate_field_grid(dimension_t dimension) {
  Item** grid = malloc(dimension.height * sizeof(*grid));
  for (size_t i = 0; i < dimension.height; i++) {
    grid[i] = malloc(dimension.width * sizeof(*grid[i]));
    for (size_t j = 0; j < dimension.width; j++) {
      grid[i][j] = NULL;
    }
  }

  return grid;
}

/*----------------------------------------------------------------------------*/

// Free field's grid as C-matrix in the heap
void free_field_grid(Item** grid, dimension_t dimension) {
  // This function should always be used on an initialized field,
  // whose grid was allocated previously
  assert(grid != NULL);

  for (size_t i = 0; i < dimension.height; i++) {
    free(grid[i]);
    grid[i] = NULL;
  }
  free(grid);
  grid = NULL;
}

/*----------------------------------------------------------------------------*/

bool position_is_beyond_limit_of_field(Field field, position_t p) {
  if (field == NULL) return false;
  return p.i > field->dimension.height-1 || p.j > field->dimension.width-1;
}

/*----------------------------------------------------------------------------*/

void print_item_in_field(Item item) {
  if (item == NULL) {
    putchar(' ');
    return;
  }

  putchar(get_item_symbol(item));
}

/*----------------------------------------------------------------------------*/
