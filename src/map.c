// Standard headers
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Internal headers
#include "dimension.h"

// Main header
#include "map.h"

/*----------------------------------------------------------------------------*/
/*                        PRIVATE STRUCT IMPLEMENTATION                       */
/*----------------------------------------------------------------------------*/

struct map {
  dimension_t dimension;
  char** grid;
};

/*----------------------------------------------------------------------------*/
/*                          PRIVATE FUNCTIONS HEADERS                         */
/*----------------------------------------------------------------------------*/

dimension_t read_map_dimension_from_map_file(FILE* map_file);
void read_map_grid_from_map_file(char** grid,
                                 dimension_t dimension,
                                 FILE* map_file);

char** allocate_map_grid(dimension_t dimension);
void free_map_grid(char** grid, dimension_t dimension);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

Map new_map(const char* map_path) {
  FILE* map_file = fopen(map_path, "r");

  if (map_file == NULL) {
    fprintf(stderr, "ERROR: Could not open file %s\n", map_path);
    return NULL;
  }

  Map map = malloc(sizeof(*map));

  map->dimension = read_map_dimension_from_map_file(map_file);
  map->grid = allocate_map_grid(map->dimension);

  read_map_grid_from_map_file(map->grid, map->dimension, map_file);

  fclose(map_file);

  return map;
}

/*----------------------------------------------------------------------------*/

void delete_map(Map map) {
  if (map == NULL) return;

  free_map_grid(map->grid, map->dimension);
  map->grid = NULL;

  map->dimension = (dimension_t){ 0, 0 };

  free(map);
}

/*----------------------------------------------------------------------------*/

void print_map(Map map) {
  if (map == NULL) return;

  for (size_t i = 0; i < map->dimension.height; i++) {
    for (size_t j = 0; j < map->dimension.width; j++) {
      putchar(map->grid[i][j]);
    }
    putchar('\n');
  }
  putchar('\n');
}

/*----------------------------------------------------------------------------*/

dimension_t get_map_dimension(Map map) {
  if (map == NULL) return (dimension_t){ 0, 0 };
  return map->dimension;
}

/*----------------------------------------------------------------------------*/

char get_map_symbol(Map map, position_t position) {
  if (map == NULL) return '\0';
  return map->grid[position.i][position.j];
}

/*----------------------------------------------------------------------------*/
/*                             PRIVATE FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

dimension_t read_map_dimension_from_map_file(FILE* map) {
  dimension_t dimension = { 0, 0 };

  int result = fscanf(map, "%lu,%lu\n",
      &dimension.height, &dimension.width);

  if (result == EOF) {
    fprintf(stderr, "ERROR: Map does not specify height and width\n");
  }

  return dimension;
}

/*----------------------------------------------------------------------------*/

void read_map_grid_from_map_file(char** grid,
                                 dimension_t dimension,
                                 FILE* map_file) {
  char symbol = EOF;
  size_t line = 0;
  size_t column = 0;

  while ((symbol = getc(map_file)) != EOF) {
    if (symbol == '\n') {
      // Warns if newline is before width, ignores all characters after it
      if (line < dimension.height && column < dimension.width) {
        fprintf(stderr, "WARNING: Line %ld does not have at least %ld columns\n",
            line, dimension.width);
      }

      if (line < dimension.height && column > dimension.width) {
        fprintf(stderr, "WARNING: Line %ld has more than %ld columns\n",
            line, dimension.width);
      }

      // Advances line, resets column
      line++; column = 0;

      continue;
    }

    // Regular symbol within height and width
    if (line < dimension.height && column < dimension.width) {
      grid[line][column] = symbol;
    }

    // Advances column
    column++;
  }

  // Warns if there are less lines than height
  if (line < dimension.height) {
    fprintf(stderr, "WARNING: Map does not have at least %ld lines\n",
        dimension.width);
  }
}

/*----------------------------------------------------------------------------*/

// Allocate map's grid as C-matrix in the heap
char** allocate_map_grid(dimension_t dimension) {
  char** grid = malloc(dimension.height * sizeof(*grid));
  for (size_t i = 0; i < dimension.height; i++) {
    grid[i] = malloc(dimension.width * sizeof(*grid[i]));
    for (size_t j = 0; j < dimension.width; j++) {
      grid[i][j] = '\0';
    }
  }

  return grid;
}

/*----------------------------------------------------------------------------*/

// Free map's grid as C-matrix in the heap
void free_map_grid(char** grid, dimension_t dimension) {
  // This function should always be used on an initialized map,
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
