#ifndef MAP_H
#define MAP_H

// Internal headers
#include "dimension.h"
#include "position.h"

// Structs

/**
 * A map is 2D grid memory representation of the layout of a Game.
 */
typedef struct map* Map;

// Functions
Map new_map(const char* map_path);
void delete_map(Map map);

void print_map(Map map);

dimension_t get_map_dimension(Map map);
char get_map_symbol(Map map, position_t position);

#endif // MAP_H
