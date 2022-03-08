// Standard headers
#include <stdio.h>
#include <stdlib.h>

// Internal headers
#include "dimension.h"
#include "game.h"

// Macros
#define STANDARD_FIELD_DIMENSION (dimension_t) { 10, 10 }
#define STANDARD_MAX_TURNS 42

/*----------------------------------------------------------------------------*/
/*                               MAIN FUNCTION                                */
/*----------------------------------------------------------------------------*/

int main() {
  printf("## RUGBY GAME ##\n\n");

  Game game = new_game(STANDARD_FIELD_DIMENSION);
  play_game(game, STANDARD_MAX_TURNS);
  delete_game(game);

  return EXIT_SUCCESS;
}
