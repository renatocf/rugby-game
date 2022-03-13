// Standard headers
#include <stdlib.h>

// Internal headers
#include "player.h"

// Main header
#include "spy.h"

/*----------------------------------------------------------------------------*/
/*                        PRIVATE STRUCT IMPLEMENTATION                       */
/*----------------------------------------------------------------------------*/

struct spy {
  Player player;
  size_t number_uses;
};

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

Spy new_spy(Player player) {
  Spy spy = malloc(sizeof(*spy));

  spy->player = player;
  spy->number_uses = 0;

  return spy;
}

/*----------------------------------------------------------------------------*/

void delete_spy(Spy spy) {
  if (spy == NULL) return;

  spy->number_uses = 0;
  spy->player = NULL;

  free(spy);
}

/*----------------------------------------------------------------------------*/

position_t get_spy_position(Spy spy) {
  if (spy == NULL) return (position_t) { 0, 0 };

  position_t player_position = get_player_position(spy->player);
  spy->number_uses++;

  return player_position;
}

/*----------------------------------------------------------------------------*/

size_t get_spy_number_uses(Spy spy) {
  if (spy == NULL) return 0;

  return spy->number_uses;
}
