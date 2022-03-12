// Standard headers
#include <stdio.h>
#include <stdlib.h>

// Main header
#include "item.h"

/*----------------------------------------------------------------------------*/
/*                        PRIVATE STRUCT IMPLEMENTATION                       */
/*----------------------------------------------------------------------------*/

struct item {
  char symbol;
  bool is_movable;
  position_t position;
};

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

Item new_item(char symbol, bool is_movable) {
  Item item = malloc(sizeof(*item));

  item->symbol = symbol;
  item->is_movable = is_movable;
  item->position = (position_t) INVALID_POSITION;

  return item;
}

/*----------------------------------------------------------------------------*/

void delete_item(Item item) {
  if (item == NULL) return;

  free(item);
  item = NULL;
}

/*----------------------------------------------------------------------------*/

bool is_item_movable(Item item) {
  if (item == NULL) return false;
  return item->is_movable;
}

/*----------------------------------------------------------------------------*/

char get_item_symbol(Item item) {
  if (item == NULL) return '\0';
  return item->symbol;
}

/*----------------------------------------------------------------------------*/

position_t get_item_position(Item item) {
  if (item == NULL) return (position_t) INVALID_POSITION;
  return item->position;
}

/*----------------------------------------------------------------------------*/

void set_item_position(Item item, position_t new_position) {
  if (item == NULL) return;
  item->position = new_position;
}

/*----------------------------------------------------------------------------*/

bool equal_items(Item p1, Item p2) {
  if (p1 == NULL || p2 == NULL) return false;
  return p1 == p2;
}

/*----------------------------------------------------------------------------*/
