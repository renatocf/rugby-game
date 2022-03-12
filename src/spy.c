// Standard headers
#include <stdlib.h>

// Internal headers
#include "item.h"

// Main header
#include "spy.h"

/*----------------------------------------------------------------------------*/
/*                        PRIVATE STRUCT IMPLEMENTATION                       */
/*----------------------------------------------------------------------------*/

struct spy {
  Item item;
  size_t number_uses;
};

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

Spy new_spy(Item item) {
  Spy spy = malloc(sizeof(*spy));

  spy->item = item;
  spy->number_uses = 0;

  return spy;
}

/*----------------------------------------------------------------------------*/

void delete_spy(Spy spy) {
  if (spy == NULL) return;

  spy->number_uses = 0;
  spy->item = NULL;

  free(spy);
}

/*----------------------------------------------------------------------------*/

position_t get_spy_position(Spy spy) {
  if (spy == NULL) return (position_t) INVALID_POSITION;

  position_t item_position = get_item_position(spy->item);
  spy->number_uses++;

  return item_position;
}

/*----------------------------------------------------------------------------*/

size_t get_spy_number_uses(Spy spy) {
  if (spy == NULL) return 0;

  return spy->number_uses;
}
