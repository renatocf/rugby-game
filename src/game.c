// Standard headers
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Main header
#include "game.h"

/*----------------------------------------------------------------------------*/
/*                        PRIVATE STRUCT IMPLEMENTATION                       */
/*----------------------------------------------------------------------------*/

struct game {
  Field field;

  Player attacker;
  Player defender;
};

/*----------------------------------------------------------------------------*/
/*                          PRIVATE FUNCTIONS HEADERS                         */
/*----------------------------------------------------------------------------*/

void set_attacker_in_field(Field field, Player attacker);
void set_defender_in_field(Field field, Player defender);

bool has_defender_captured_attacker(Player defender, Player attacker);
bool has_attacker_arrived_end_field(Field field, Player attacker);

void move_attacker(Field field, Player attacker);
void move_defender(Field field, Player defender);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

Game new_game(dimension_t field_dimension) {
  Game game = malloc(sizeof(*game));

  game->field = new_field(field_dimension);

  game->attacker = new_player('A');
  game->defender = new_player('D');

  set_attacker_in_field(game->field, game->attacker);
  set_defender_in_field(game->field, game->defender);

  return game;
}

/*----------------------------------------------------------------------------*/

void delete_game(Game game) {
  if (game == NULL) return;

  delete_player(game->defender);
  game->defender = NULL;

  delete_player(game->attacker);
  game->attacker = NULL;

  delete_field(game->field);
  game->field = NULL;

  free(game);
}

/*----------------------------------------------------------------------------*/

void print_game(Game game) {
  if (game == NULL) return;

  print_field_grid(game->field);
}

/*----------------------------------------------------------------------------*/

void play_game(Game game, size_t max_turns) {
  if (game == NULL) return;

  printf("Turn 0\n");
  print_game(game);

  for (size_t turn = 0; turn < max_turns; turn++) {
    printf("Turn %ld\n", turn+1);

    move_attacker(game->field, game->attacker);
    move_defender(game->field, game->defender);

    print_game(game);

    if (has_attacker_arrived_end_field(game->field, game->attacker)) {
      printf("GAME OVER! Attacker wins!\n");
      return;
    }

    if (has_defender_captured_attacker(game->attacker, game->defender)) {
      printf("GAME OVER! Defender wins!\n");
      return;
    }
  }

  // A draw happens only if nobody wins before max_turns
  printf("GAME OVER! Attacker and Defender draw!\n");
}

/*----------------------------------------------------------------------------*/
/*                             PRIVATE FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

void set_attacker_in_field(Field field, Player attacker) {
  if (field == NULL || attacker == NULL) return;

  dimension_t field_dimension = get_field_dimension(field);

  position_t attacker_initial_position = {
    field_dimension.height / 2, 1 // Left side of field
  };
  add_player_to_field(field, attacker, attacker_initial_position);
}

/*----------------------------------------------------------------------------*/

void set_defender_in_field(Field field, Player defender) {
  if (field == NULL || defender == NULL) return;

  dimension_t field_dimension = get_field_dimension(field);

  position_t defender_initial_position = {
    field_dimension.height / 2, field_dimension.width-2 // Right side of field
  };
  add_player_to_field(field, defender, defender_initial_position);
}

/*----------------------------------------------------------------------------*/

bool has_defender_captured_attacker(Player defender, Player attacker) {
  if (attacker == NULL || defender == NULL) return false;

  position_t attacker_position = get_player_position(attacker);
  position_t defender_position = get_player_position(defender);

  return neighbor_positions(defender_position, attacker_position);
}

/*----------------------------------------------------------------------------*/

bool has_attacker_arrived_end_field(Field field, Player attacker) {
  if (field == NULL || attacker == NULL) return false;

  position_t attacker_position = get_player_position(attacker);
  dimension_t field_dimension = get_field_dimension(field);

  return attacker_position.j == field_dimension.width - 2;
}

/*----------------------------------------------------------------------------*/

void move_attacker(Field field, Player attacker) {
  // TODO: Implement Attacker logic here
  move_player_in_field(field, attacker, (direction_t) DIR_RIGHT);
}

/*----------------------------------------------------------------------------*/

void move_defender(Field field, Player defender) {
  // TODO: Implement Defender logic here
  move_player_in_field(field, defender, (direction_t) DIR_LEFT);
}

/*----------------------------------------------------------------------------*/
