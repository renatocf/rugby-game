// Standard headers
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Internal headers
#include "attacker.h"
#include "defender.h"
#include "dimension.h"
#include "map.h"
#include "game.h"

// Macros
#define STANDARD_FIELD_DIMENSION (dimension_t) { 10, 10 }
#define STANDARD_MAX_NUMBER_SPIES 1LU
#define STANDARD_MAX_TURNS 42

/*----------------------------------------------------------------------------*/
/*                       AUXILIARY FUNCTIONS DECLARATION                      */
/*----------------------------------------------------------------------------*/

Game choose_game(int argc, char** argv);
Game make_standard_game();
Game make_game_from_map(const char* map_path);

/*----------------------------------------------------------------------------*/
/*                               MAIN FUNCTION                                */
/*----------------------------------------------------------------------------*/

int main(int argc, char** argv) {
  if (argc >= 3) {
    fprintf(stderr, "USAGE: %s [map_path]\n", argv[0]);
    return EXIT_FAILURE;
  }

  printf("## RUGBY GAME ##\n\n");

  Game game = choose_game(argc, argv);
  play_game(game, STANDARD_MAX_TURNS);
  delete_game(game);

  return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/*                             AUXILIARY FUNCTIONS                            */
/*----------------------------------------------------------------------------*/

Game choose_game(int argc, char** argv) {
  switch (argc) {
    case 1: return make_standard_game();
    case 2: return make_game_from_map(argv[1]);
    default:
      // argc should not be any other number
      assert(false);
  }
}

/*----------------------------------------------------------------------------*/

Game make_standard_game() {
  Game game = new_game(
      STANDARD_FIELD_DIMENSION,
      STANDARD_MAX_NUMBER_SPIES,
      execute_attacker_strategy,
      execute_defender_strategy);

  return game;
}

/*----------------------------------------------------------------------------*/

Game make_game_from_map(const char* map_path) {
  Map map = new_map(map_path);

  Game game = new_game_from_map(
      map,
      STANDARD_MAX_NUMBER_SPIES,
      execute_attacker_strategy,
      execute_defender_strategy);

  delete_map(map);

  return game;
}

/*----------------------------------------------------------------------------*/
