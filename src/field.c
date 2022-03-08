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
  Player** grid;
};

/*----------------------------------------------------------------------------*/
/*                          PRIVATE FUNCTIONS HEADERS                         */
/*----------------------------------------------------------------------------*/

Player** allocate_field_grid(dimension_t dimension);
void free_field_grid(Player** grid, dimension_t dimension);

bool position_is_border_of_field(Field field, position_t p);
bool position_is_beyond_border_of_field(Field field, position_t p);

void print_player_in_field(Player player);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

Field new_field(dimension_t dimension) {
  if (dimension.height < FIELD_MIN_DIMENSION.height) {
    fprintf(stderr, "Height must be at least %ld because of the Field's borders\n",
            FIELD_MIN_DIMENSION.height);
    return NULL;
  }

  if (dimension.width < FIELD_MIN_DIMENSION.width) {
    fprintf(stderr, "Width must be at least %ld because of the Field's borders\n",
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

  field->dimension = (dimension_t){ 0, 0 };

  free(field);
}

/*----------------------------------------------------------------------------*/

dimension_t get_field_dimension(Field field) {
  if (field == NULL) return (dimension_t){ 0, 0 };
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
      position_t position = { i, j };

      putchar('|');
      if (position_is_border_of_field(field, position))
        putchar('X');
      else
        print_player_in_field(field->grid[i][j]);
    }
    putchar('|');
    putchar('\n');
  }
  putchar('\n');
}

/*----------------------------------------------------------------------------*/

void add_player_to_field(Field field, Player player, position_t position) {
  if (field == NULL || player == NULL) return;

  if (position_is_beyond_border_of_field(field, position)) {
    fprintf(stderr, "ERROR: Player '%c' must be within the borders of the field!\n",
        get_player_symbol(player));
    return;
  }

  field->grid[position.i][position.j] = player;
  set_player_position(player, position);
}

/*----------------------------------------------------------------------------*/

void move_player_in_field(Field field, Player player, direction_t direction) {
  if (field == NULL || player == NULL) return;

  position_t player_position = get_player_position(player);

  // Given how players are added to the field, their position
  // should never be in the border of the field
  assert(!position_is_border_of_field(field, player_position));

  position_t new_position = move_position(get_player_position(player), direction);

  // Item cannot be moved if position is already occupied
  if (position_is_border_of_field(field, new_position)) return;

  // Change current position in the grid
  field->grid[new_position.i][new_position.j] = player;
  field->grid[player_position.i][player_position.j] = NULL;
  set_player_position(player, new_position);
}

/*----------------------------------------------------------------------------*/
/*                             PRIVATE FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

// Allocate field's grid as C-matrix in the heap
Player** allocate_field_grid(dimension_t dimension) {
  Player** grid = malloc(dimension.height * sizeof(*grid));
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
void free_field_grid(Player** grid, dimension_t dimension) {
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

bool position_is_border_of_field(Field field, position_t p) {
  if (field == NULL) return false;
  return p.i == 0 || p.j == 0 || p.i == field->dimension.height-1 || p.j == field->dimension.width-1;
}

/*----------------------------------------------------------------------------*/

bool position_is_beyond_border_of_field(Field field, position_t p) {
  if (field == NULL) return false;
  return p.i == 0 || p.j == 0 || p.i > field->dimension.height-1 || p.j > field->dimension.width-1;
}

/*----------------------------------------------------------------------------*/

void print_player_in_field(Player player) {
  if (player == NULL) {
    putchar(' ');
    return;
  }

  putchar(get_player_symbol(player));
}

/*----------------------------------------------------------------------------*/
