// Standard headers
#include <stdio.h>
#include <stdlib.h>

// Internal headers
#include "attacker.h"
#include "defender.h"
#include "dimension.h"
#include "game.h"

// Macros
#define STANDARD_FIELD_DIMENSION (dimension_t){ 10, 10 }
#define STANDARD_MAX_NUMBER_SPIES 1LU
#define STANDARD_MAX_TURNS 42

/*----------------------------------------------------------------------------*/
/*                               MAIN FUNCTION                                */
/*----------------------------------------------------------------------------*/

int main() {
  printf("## RUGBY GAME ##\n\n");

  Game game = new_game(
      STANDARD_FIELD_DIMENSION,
      STANDARD_MAX_NUMBER_SPIES,
      execute_attacker_strategy,
      execute_defender_strategy);

  play_game(game, STANDARD_MAX_TURNS);

  delete_game(game);

  return EXIT_SUCCESS;
}
