#ifndef ITEM_H
#define ITEM_H

// Standard headers
#include <stdbool.h>

// Internal headers
#include "position.h"

// Structs

/**
 * An item is represented by a symbol and its current position in a field.
 */
typedef struct item* Item;

// Functions
Item new_item(char symbol, bool is_movable);
void delete_item(Item item);

bool is_item_movable(Item item);

char get_item_symbol(Item item);
position_t get_item_position(Item item);
void set_item_position(Item item, position_t new_position);

bool equal_items(Item p1, Item p2);

#endif // ITEM_H
