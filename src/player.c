// Standard headers
#include <stdio.h>
#include <stdlib.h>

// Main header
#include "player.h"

/*----------------------------------------------------------------------------*/
/*                        PRIVATE STRUCT IMPLEMENTATION                       */
/*----------------------------------------------------------------------------*/

struct player {
  char symbol;
  position_t position;
};

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

Player new_player(char symbol) {
  Player player = malloc(sizeof(*player));

  player->symbol = symbol;
  player->position = (position_t){ 0, 0 };

  return player;
}

/*----------------------------------------------------------------------------*/

void delete_player(Player player) {
  if (player == NULL) return;

  free(player);
  player = NULL;
}

/*----------------------------------------------------------------------------*/

char get_player_symbol(Player player) {
  if (player == NULL) return '\0';
  return player->symbol;
}

/*----------------------------------------------------------------------------*/

position_t get_player_position(Player player) {
  if (player == NULL) return (position_t) { 0, 0 };
  return player->position;
}

/*----------------------------------------------------------------------------*/

void set_player_position(Player player, position_t new_position) {
  if (player == NULL) return;
  player->position = new_position;
}

/*----------------------------------------------------------------------------*/

bool equal_players(Player p1, Player p2) {
  if (p1 == NULL || p2 == NULL) return false;
  return p1->symbol == p2->symbol;
}

/*----------------------------------------------------------------------------*/
